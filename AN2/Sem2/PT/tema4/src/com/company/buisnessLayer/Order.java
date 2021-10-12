package com.company.buisnessLayer;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Date;

public class Order implements Serializable {
    private ArrayList<MenuItem> order = new ArrayList<>();
    private static int counter=0;
    private int clientId;
    private int orderId = 0;
    private Date date;
    private String stringOrder;

    public String getStringOrder() {
        return stringOrder;
    }

    public void setStringOrder(String stringOrder) {
        this.stringOrder = stringOrder;
    }

    public Order(ArrayList<MenuItem> menu, int clientId)
    {
        counter++;
        this.orderId = counter;
        order.addAll(menu);
        this.clientId = clientId;
        date = new Date();
    }


    public ArrayList<MenuItem> getOrder() {
        return order;
    }

    public void setOrder(ArrayList<MenuItem> order) {
        this.order = order;
    }

    public int getOrderId()
    {
        return orderId;
    }

    public static int getCounter() {
        return counter;
    }

    public static void setCounter(int param) {
        counter = param;
    }

    public int getClientId() {
        return clientId;
    }

    public void setClientId(int clientId) {
        this.clientId = clientId;
    }

    public Date getDate() {
        return date;
    }

    public void addProduct(MenuItem menuItem)
    {
        this.order.add(menuItem);
    }

    public double getPrice()
    {
        double sum = 0;
        for(MenuItem menuItem : order)
            sum = sum + menuItem.getPrice();
        return sum;
    }


}
