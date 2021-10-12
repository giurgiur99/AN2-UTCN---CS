package com.company;

import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.TimeUnit;
import java.util.logging.*;

public class Shop {
    private ArrayList<Queue> queues;
    private ArrayList<String> toBePrinted;
    private int peakWaitingTime=0, peakHour=0, averageWaitingTime=0, noOfQueues=0;
    private int numberOfClients, LOS, lengthOfSimulation, minArrivingInterval, maxArrivingInterval, minServiceTime, maxServiceTime;
    private GUI gui;
    private String simulationTimeText;
    private String nextClientText;
    private String averageTimeText;
    private String peakWaitingTimeText;
    private String peakHourText;
    private Logger logger;
    FileHandler fileHandler;

    public Shop(int numberOfClientsParam, int los, int minArrivingIntervalParam, int maxArrivingIntervalParam, int minServiceTimeParam, int maxServiceTimeParam, int noOfQueues, ArrayList<String> where_to_print, GUI gui)
    {
        this.gui=gui;
        this.peakHourText=new String("0");
        this.numberOfClients = numberOfClientsParam;
        this.lengthOfSimulation = los;
        LOS = lengthOfSimulation;
        this.minArrivingInterval = minArrivingIntervalParam;
        this.maxArrivingInterval = maxArrivingIntervalParam;
        this.minServiceTime = minServiceTimeParam;
        this.maxServiceTime = maxServiceTimeParam;
        this.toBePrinted = where_to_print;
        this.noOfQueues = noOfQueues;
        this.logger = Logger.getLogger("queues");
        this.queues = new ArrayList<Queue>(noOfQueues);
        for (int i = 0; i < noOfQueues; i++) {
            Queue q = new Queue();
            this.queues.add(q);
        }
        this.peakHour = 0;
        this.peakWaitingTime = 0;
        this.averageWaitingTime = 0;
    }

    public void startSimulation() throws InterruptedException {

        Thread thread = new Thread(new Runnable() {

            public void run() {
                try {
                    fileHandler = new FileHandler("C:\\Users\\TheRa\\Desktop\\Utcn\\AN2\\Sem2\\PT\\Labs\\Lab2\\log.log");
                } catch (IOException e1) {
                    e1.printStackTrace();
                }

                logger.addHandler(fileHandler);
                SimpleFormatter formatter = new SimpleFormatter();
                fileHandler.setFormatter(formatter);
                logger.info("Queue simulation");
                int clientArrival = 0;
                int serviceTime = 0;
                while (lengthOfSimulation > 0) {
                    if (clientArrival == 0) {
                            if(maxArrivingInterval/numberOfClients!=0 && minArrivingInterval/numberOfClients!=0)
                                 clientArrival = (int) (Math.random() * (maxArrivingInterval/numberOfClients - minArrivingInterval/numberOfClients) + 1) + minArrivingInterval/numberOfClients;
                            serviceTime = (int) (Math.random() * (maxServiceTime - minServiceTime) + 1) + minServiceTime;
                            Client client = new Client(serviceTime);
                            addClient(client);
                            numberOfClients--;
                        }
                     else
                    {
                        clientArrival--;
                        serviceTime--;
                    }
                    int currentTotalWaitingTime=0;
                    for (Queue q : queues)
                        currentTotalWaitingTime += q.getWaitingTime();
                    averageWaitingTime +=currentTotalWaitingTime;

                    if(currentTotalWaitingTime > peakWaitingTime)
                    {
                        peakWaitingTime =currentTotalWaitingTime;
                        peakHour = LOS- lengthOfSimulation;
                    }

                    nextEvent();
                    printOnScreen();

                    try {
                        TimeUnit.SECONDS.sleep(1);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }


                    simulationTimeText="Simulation Time Remaining:" + Integer.toString(lengthOfSimulation) + " seconds";
                    //nextClientText="Next client:" + Integer.toString(clientArrival) + " seconds";
                    averageTimeText="Average waiting time:" + Double.valueOf(getAverage()).toString() + " seconds";
                    peakHourText="Peak hour of simulation:" + Integer.valueOf(getPeakHour()).toString() + " seconds";
                    peakWaitingTimeText="Peak waiting second :" + Integer.valueOf(getPeakWaitingTime()).toString() ;

                    lengthOfSimulation--;

                    if( (numberOfClients == 0 )  && ( (serviceTime == 0) || (clientArrival > lengthOfSimulation) ))
                    {
                        simulationTimeText="SIMULATION ENDED";
                        nextClientText="SIMULATION ENDED";
                        printOnScreen();
                        return;
                       // System.exit(0);
                    }

                }
            }
        });
        thread.start();

    }

    public void addClient(Client c) {
        int minQueue = 0, minWaitingTime = 10000;
        for (Queue q : this.queues) {
            if (q.getWaitingTime() > this.peakWaitingTime) {
                this.peakWaitingTime = q.getWaitingTime();
                this.peakHour = this.LOS - this.lengthOfSimulation;
            }
            if (q.getWaitingTime() < minWaitingTime) {
                minWaitingTime = q.getWaitingTime();
                minQueue = this.queues.indexOf(q);
            }
        }
        this.queues.get(minQueue).addClient(c);
        logger.info("A new client joined queue(" + (minQueue+1) + ") at time(" + (LOS- lengthOfSimulation) + ")");
    }


    public void nextEvent() {
        ArrayList<Thread> threads = new ArrayList<Thread>(noOfQueues);
        for (Queue q : this.queues) {
            Thread thread = new Thread(new Runnable() {
                public void run() {
                    q.nextTime(logger,queues.indexOf(q),(LOS - lengthOfSimulation));

                }
            });
            threads.add(thread);
            thread.start();

        }
        for (Thread t : threads) {
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


    public synchronized void printOnScreen() {
        this.toBePrinted = new ArrayList<String>();
        for (int i = 0; i < noOfQueues; i++) {
            String text = new String("QUEUE " + (i+1) + "\n\n" + this.queues.get(i).toString());
            this.toBePrinted.add(text);
        }
        gui.rewriteGUI(this.toBePrinted,this.nextClientText,this.simulationTimeText,this.averageTimeText,this.peakHourText,this.peakWaitingTimeText);
    }

    public double getAverage() {
        double average=this.averageWaitingTime;
        average*=100;
        average=average/(this.LOS - this.lengthOfSimulation) / this.noOfQueues;
        average=Math.round(average);
        average/=100;
        return average;
    }

    public int getPeakHour() {
        return this.peakHour;
    }

    public int getPeakWaitingTime() {
        return this.peakWaitingTime;
    }

}


