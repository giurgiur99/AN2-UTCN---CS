close all
clc
% ???? c i t e s t e d a t e l e din ECGdata . txt ?????
fileID = fopen ('ECGdata.txt','r'); % de s chide ECGdata . txt pentru c i t i r e
A = fscanf(fileID, '%f %f',[2,Inf]); % c i t e s t e d a t e l e din f i s i e r in mat r i cea A
fclose(fileID); %inchide ECGdata.txt
time = A(1,:); % s al veaza prima linie de date in variabila "timp"
necg = A(2,:) ; % s al veaza a doua linie de date in variabila "necg"

figure, plot(time, necg), grid on;
xlabel('t(sec)'), ylabel('ECG normalizat'); 