package com.company;
public class Client {
    private int serviceTime, waitingTime;

    public Client(int serviceTimeParam) {
        this.serviceTime = serviceTimeParam;
        this.waitingTime = 0;
    }

    public int getServiceTime() {
        return this.serviceTime;
    }

    public int getWaitingTime() {
        return this.waitingTime;
    }

    public void setServiceTime(int st) {
        this.serviceTime = st;
    }

    public void setWaitingTime(int wt) {
        this.waitingTime = wt;
    }

    @Override
    public String toString()
    {
        return " waits "+ this.getWaitingTime() + " seconds\n";
    }
}


