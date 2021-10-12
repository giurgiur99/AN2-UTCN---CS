package com.company.DataLayer;

import com.company.buisnessLayer.DeliveryService;
import com.company.buisnessLayer.MenuItem;
import com.company.buisnessLayer.Order;
import com.company.buisnessLayer.User;

import java.awt.*;
import java.io.*;
import java.util.ArrayList;
import java.util.HashSet;

public class Serializator {
    static String file1 = "f1.txt";
    static String file2 = "f2.txt";
    static String file3 = "f3.txt";
    static String file4 = "f4.txt";

    public static void serialization(HashSet<Order> orders, ArrayList<User> users, HashSet<MenuItem> menuItems){
        PrintWriter ser = null;
        try {
            ser = new PrintWriter(file1);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        ser.print("");
        ser.close();
        //
        try {
            ser = new PrintWriter(file2);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        ser.print("");
        ser.close();

        try {
            ser = new PrintWriter(file3);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        ser.print("");
        ser.close();
        try
        {
            FileOutputStream out = new FileOutputStream(file1);
            ObjectOutputStream out1 = new ObjectOutputStream(out);
            out1.writeObject(orders);
            out1.close();
            out.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        try
        {
            FileOutputStream out = new FileOutputStream(file2);
            ObjectOutputStream out1 = new ObjectOutputStream(out);
            out1.writeObject(menuItems);
            out1.close();
            out.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        try
        {
            FileOutputStream out = new FileOutputStream(file3);
            ObjectOutputStream out1 = new ObjectOutputStream(out);
            out1.writeObject(users);
            out1.close();
            out.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        try
        {
            FileOutputStream out = new FileOutputStream(file4);
            ObjectOutputStream out1 = new ObjectOutputStream(out);
            out1.writeObject(User.getCounter());
            out1.writeObject(Order.getCounter());
            out1.close();
            out.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    public static void deserialization(){
        int setCounterUser;
        int setCounterOrder;
        ArrayList<User> users1;
        HashSet<Order> orders1;
        HashSet<com.company.buisnessLayer.MenuItem> menuItems1;
        try
        {
            FileInputStream out = new FileInputStream(file1);
            ObjectInputStream out1 = new ObjectInputStream(out);

            orders1 = (HashSet<Order>) out1.readObject();

            out1.close();
            out.close();
        } catch (IOException e)
        {
            e.printStackTrace();
            return;
        }
        catch (ClassNotFoundException e2)
        {
            System.out.println("Class not found");
            e2.printStackTrace();
            return;
        }

        try
        {
            FileInputStream out = new FileInputStream(file2);
            ObjectInputStream out1 = new ObjectInputStream(out);

            menuItems1 = (HashSet<MenuItem>) out1.readObject();

            out1.close();
            out.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
            return;
        }
        catch (ClassNotFoundException e2)
        {
            System.out.println("Class not found");
            e2.printStackTrace();
            return;
        }
        try
        {
            FileInputStream out = new FileInputStream(file3);
            ObjectInputStream out1 = new ObjectInputStream(out);

            users1 = (ArrayList<User>) out1.readObject();

            out1.close();
            out.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
            return;
        }
        catch (ClassNotFoundException e2)
        {
            System.out.println("Class not found");
            e2.printStackTrace();
            return;
        }
        try
        {
            FileInputStream out = new FileInputStream(file4);
            ObjectInputStream out1 = new ObjectInputStream(out);

            setCounterUser = (int) out1.readObject();
            setCounterOrder = (int) out1.readObject();

            out1.close();
            out.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
            return;
        }
        catch (ClassNotFoundException e1)
        {
            System.out.println("Class not found");
            e1.printStackTrace();
            return;
        }
        User.setCounter(setCounterUser);
        Order.setCounter(setCounterOrder);
        DeliveryService.loadInfo(orders1, users1, menuItems1);
    }
}
