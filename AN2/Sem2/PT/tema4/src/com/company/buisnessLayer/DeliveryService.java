package com.company.buisnessLayer;

import com.company.DataLayer.Serializator;

import javax.swing.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.List;
import java.util.stream.Collectors;

public class DeliveryService extends JPanel implements IDeliveryServiceProcessing{

    private static HashSet<MenuItem> menu;
    private static HashSet<Order> orders;
    public ArrayList<Object> strings;

    public DeliveryService()
    {
        menu = new HashSet<>();
        orders = new HashSet<>();
    }

    @Override
    public ArrayList<Product> importBaseProducts() {
        Scanner sc = null;
        try {
            sc = new Scanner(new File( "products.csv"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        ArrayList<Product> products = new ArrayList<>();
            int i = 0;
            sc.useDelimiter(" ");
            sc.nextLine();
            while (sc.hasNextLine())
            {
                Scanner sc2 = new Scanner(sc.nextLine());
                sc2.useDelimiter(",");
                Product product = new Product(sc2.next(),Double.parseDouble(sc2.next()),Double.parseDouble(sc2.next()),Double.parseDouble(sc2.next()),Double.parseDouble(sc2.next()),Double.parseDouble(sc2.next()),Double.parseDouble(sc2.next()));
                products.add(product);
            }
            sc.close();

        menu.addAll(products);
        return products;
    }

    @Override
    public void addProduct(MenuItem m) {
        menu.add(m);
    }

    @Override
    public void deleteProduct(MenuItem m) {
        menu.remove(m);
    }

    @Override
    public void editProduct(MenuItem m1, MenuItem m2) {
        for(MenuItem menuItem : menu)
            if(menuItem.getTitle().equals(m2.getTitle()))
            {
                menuItem.setTitle(m1.getTitle());
                menuItem.setRating(m1.getRating());
                menuItem.setCalories(m1.getCalories());
                menuItem.setProtein(m1.getProtein());
                menuItem.setFat(m1.getFat());
                menuItem.setSodium(m1.getSodium());
                menuItem.setPrice(m1.getPrice());

            }
    }

    @Override
    public HashSet<Order> getOrders() {
        return orders;
    }

    @Override
    public Order addOrder(ArrayList<MenuItem> menus, int clientID) {
        Order order = new Order(menus, clientID);
        orders.add(order);
        System.out.println("Client ID " + clientID);
        notifyClient(order);

        return order;
    }

    @Override
    public HashSet<MenuItem> getMenu() {
        return menu;
    }

    @Override
    public MenuItem find(String title) {
        for(MenuItem m: menu) {
            if(m.getTitle().equals(title)) {
                return m;
            }
        }
        return null;
    }

    @Override
    public List<MenuItem> search(String s1, String s2, String s3, String s4, String s5, String s6, String s7) {
        List<MenuItem> stream = menu.stream()
                .filter(menuItem1 -> menuItem1.getTitle().toLowerCase().contains(s1.toLowerCase()))
                .filter(menuItem1 -> Float.parseFloat(s2) == menuItem1.getRating())
                .filter(menuItem1 -> Integer.parseInt(s3) == menuItem1.getCalories())
                .filter(menuItem1 -> Integer.parseInt(s4) == menuItem1.getProtein())
                .filter(menuItem1 -> Integer.parseInt(s5) == menuItem1.getFat())
                .filter(menuItem1 -> Integer.parseInt(s6) == menuItem1.getSodium())
                .filter(menuItem1 -> Integer.parseInt(s7) == menuItem1.getPrice())
                .collect(Collectors.toList());
        return stream;
    }

    @Override
    public void notifyClient(Order order) {
        String str = "";
        str = str + "Order ID " +  order.getOrderId() + ", " + "Client ID " +order.getClientId() + ", ";
        for(MenuItem m: order.getOrder()){
            str = str + m.getTitle() + ", ";
        }
        str = str + order.getPrice();
        System.out.println((str));
        order.setStringOrder(str);
    }

    public static void loadInfo(HashSet<Order> orders, ArrayList<User> users, HashSet<MenuItem> menuItems){
        DeliveryService.orders.addAll(orders);
        menu.addAll(menuItems);
        Model.getUsers().addAll(users);
    }

    public void storeInfo()
    {
        Serializator.serialization(orders,Model.getUsers(),menu);
    }

}
