package com.company.buisnessLayer;

import javax.swing.*;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

public interface IDeliveryServiceProcessing {
    ArrayList<Product> importBaseProducts();
    void addProduct(MenuItem m);
    void deleteProduct(MenuItem m);
    void editProduct(MenuItem m1, MenuItem m2);
    HashSet<Order> getOrders();
    Order addOrder(ArrayList<MenuItem> menus, int clientID);
    HashSet<MenuItem> getMenu();
    MenuItem find(String title);
    List<MenuItem> search(String s1, String s2, String s3, String s4, String s5, String s6, String s7);
    void notifyClient(Order order);

}
