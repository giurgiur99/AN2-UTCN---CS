#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

char readData[50];
int myVariant = 98835;
int pingPongTextSize = 4;
int readDataTextSize;
int connectTextSize = 7, errorSharedMemTextSize = 5, succesSharedMemTextSize = 7;
int request, response;
int sharedMem, initialSharedMem, createShareMemoryBytes, createShareMemorySize = 10;
char *shared_char = NULL;
int  writeSharedMemSize=12;
unsigned int offset, value;
void *ptr,*mapFile;
int fileNameSize, mapFileSharedMemSize=8, fileSharedMem;
struct stat st;
int fileSize;
char fileNameMappedMem[100];
int readFromFileOffset, readFromFileOffsetBytes;
unsigned int sectionNo, offset, noOfBytes, sc;

void exitSharedMemory()
{
    close(response);
    close(request);
    unlink("RESP_PIPE_98835");
}


void readFromFileSectionRequest()
{
    read(request, &sectionNo, 4);
    read(request, &offset, 4);
    read(request, &noOfBytes, 4);
    int readFromFileSectionRequestTextSize = 22;
    write(response, &readFromFileSectionRequestTextSize, 1);
    write(response, "READ_FROM_FILE_SECTION", readFromFileSectionRequestTextSize);
    if(offset > 0)
    {
        write(response, &succesSharedMemTextSize, 1);
        write(response, "SUCCES", succesSharedMemTextSize);
    }
    else
    {
        write(response, &errorSharedMemTextSize, 1);
        write(response, "ERROR", errorSharedMemTextSize);
    }
    
}

void readFromFileOffsetRequest()
{
    read(request, &readFromFileOffset, 4);
    read(request, &readFromFileOffsetBytes, 4);
    int readFromFileOffsetTextSize = 21;
    write(response, &readFromFileOffsetTextSize, 1);
    write(response, "READ_FROM_FILE_OFFSET",readFromFileOffsetTextSize);
    if(initialSharedMem > 0 && mapFile > 0 && (readFromFileOffsetBytes) < fileSize)
    {

        write(response, &succesSharedMemTextSize, 1 );
        write(response, "SUCCES", succesSharedMemTextSize );
    }
    else
    {
        write(response, &errorSharedMemTextSize, 1);
        write(response, "ERROR", errorSharedMemTextSize);
    }


}

void mapFileSharedMem()
{
    read(request, &fileNameSize, 1);
    read(request, fileNameMappedMem, fileNameSize);
    fileNameMappedMem[fileNameSize] = '\0';

    write(response, &mapFileSharedMemSize, 1);
    write(response,"MAP_FILE", mapFileSharedMemSize);
    
    fileSharedMem = open(fileNameMappedMem,O_RDONLY);
    if(fileSharedMem > 0)
    {
        stat(fileNameMappedMem, &st);
        fileSize = st.st_size;
        mapFile = mmap(0, fileSize, PROT_READ , MAP_SHARED , fileSharedMem, 0);
        if(mapFile == (void*)-1)
        {
             write(response, &errorSharedMemTextSize, 1);
             write(response, "ERROR", errorSharedMemTextSize);
        }
        write(response, &succesSharedMemTextSize, 1);
        write(response, "SUCCESS", succesSharedMemTextSize);
    }
    else
    {
        write(response, &errorSharedMemTextSize, 1);
        write(response, "ERROR", errorSharedMemTextSize);
    }
    close(fileSharedMem);

}

void writeSharedMem()
{
    read(request, &offset, 4);
    read(request, &value, 4);
    write(response, &writeSharedMemSize, 1);
    write(response, "WRITE_TO_SHM",writeSharedMemSize);
    
    if(offset + sizeof(value) < createShareMemoryBytes){
        //sprintf(ptr+of,"%u",offset);
        *(unsigned int*)(ptr + offset) = value;
        
        write(response, &succesSharedMemTextSize, 1);
        write(response, "SUCCESS", succesSharedMemTextSize);
    }
    else
    {
        write(response, &errorSharedMemTextSize, 1);
        write(response, "ERROR", errorSharedMemTextSize);
    }

    
}
void createShareMemory()
{
    read(request, &createShareMemoryBytes, sizeof(int));
    initialSharedMem = shm_open("/zKe8CTw",O_CREAT | O_RDWR ,0664);
    ftruncate(initialSharedMem, createShareMemoryBytes);
    
    write(response, &createShareMemorySize, 1);
    write(response, "CREATE_SHM", createShareMemorySize);
     if(initialSharedMem < 0)
     {  write(response, &errorSharedMemTextSize, 1);
        write(response,"ERROR",errorSharedMemTextSize);
        //printf("ERROR");
     }
     else
     {
         ptr = mmap(0, createShareMemoryBytes, PROT_READ | PROT_WRITE , MAP_SHARED , initialSharedMem, 0);
         if(ptr == (void*)-1)
        {
             write(response, &errorSharedMemTextSize, 1);
             write(response, "ERROR", errorSharedMemTextSize);
        }
        else{
         write(response, &succesSharedMemTextSize, 1);
         write(response, "SUCCESS", succesSharedMemTextSize);
        }
         //printf("SUCCESS");
     }


    
}

void pingPong()
{
    write(response, &pingPongTextSize, 1);
    write(response, "PING", pingPongTextSize);
    write(response, &pingPongTextSize, 1);
    write(response, "PONG",pingPongTextSize);
    write(response, &myVariant, sizeof(pingPongTextSize));

}

int main()
{
     if (mkfifo("RESP_PIPE_98835", 0666) == -1) 
    {
        printf("ERROR\ncannot create the response pipe\n");
        exit(-1);
    }

    request = open("REQ_PIPE_98835",O_RDONLY);
    if( request == -1)
    {
        printf("ERROR\ncannot open the request pipe\n");
        exit(-1);
    }

    response = open("RESP_PIPE_98835",O_WRONLY);
    if( response == -1)
    {
        printf("ERROR\ncannot open the response pipe\n");
        exit(-1);
    }

    write(response, &connectTextSize,1);
    write(response, "CONNECT", connectTextSize * sizeof(char));
    printf("SUCCESS\n");
    read(request, &readDataTextSize, 1);
    read(request, &readData, readDataTextSize);
    while (1){
        if(readData == strstr(readData,"PING")) pingPong();
        else if(readData == strstr(readData,"CREATE_SHM")) createShareMemory();
        else if(readData == strstr(readData,"WRITE_TO_SHM")) writeSharedMem();
        else if(readData == strstr(readData,"MAP_FILE")) mapFileSharedMem();
        else if(readData == strstr(readData,"READ_FROM_FILE_OFFSET")) readFromFileOffsetRequest();
        else if(readData == strstr(readData,"READ_FROM_FILE_SECTION")) readFromFileSectionRequest();
        else if(readData == strstr(readData,"READ_FROM_LOGICAL_SPACE_OFFSET")) break;

        read(request, &readDataTextSize, 1);
        read(request, &readData, readDataTextSize);
        if(readData == strstr(readData,"EXIT")) break;
    }
    
    exitSharedMemory();
    



    return 0;
}