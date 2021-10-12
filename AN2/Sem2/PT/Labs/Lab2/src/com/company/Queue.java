package com.company;

import java.util.ArrayList;
import java.util.logging.Logger;

public class Queue {
    private int waitingTime;
    private ArrayList<Client> clients;

    public int getWaitingTime() {
        return this.waitingTime;
    }

    public void addClient(Client client) {
        this.clients.add(client);

        client.setWaitingTime(this.waitingTime);
        this.waitingTime += client.getServiceTime();
    }
    public Client getClient(int t)
    {
        return clients.get(t);
    }

    public Queue() {
        this.clients = new ArrayList<Client>();
        this.waitingTime = 0;

    }

    public void nextTime(Logger logger, int q, int t) {
        if (this.waitingTime > 0) {
            this.waitingTime--;
            for (Client client : this.clients) {
                if (client.getWaitingTime() > 0)
                    client.setWaitingTime(client.getWaitingTime() - 1);
                else if (client.getServiceTime() > 0)
                    client.setServiceTime(client.getServiceTime() - 1);
            }
            Client client = this.clients.get(0);
            if (client.getWaitingTime() == 0 && client.getServiceTime() == 0) {
                this.clients.remove(client);
                logger.info("A client left queue(" + (q+1) + ") at time(" + t + ")");
            }
        }
    }

    @Override
    public String toString() {
        String res = new String("");
        for (Client client : this.clients) {
            if (client != this.clients.get(0))
                res += "client number " + Integer.valueOf(this.clients.indexOf(client)).toString() + client.toString();
            else
                res += "First client in queue. Remaining time :" + client.getServiceTime() + "\n";
        }
        res += "\nTOTAL WAIT:" + Integer.valueOf(this.waitingTime).toString();
        return res;
    }

}
