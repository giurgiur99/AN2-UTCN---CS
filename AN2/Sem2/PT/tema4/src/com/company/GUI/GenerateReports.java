package com.company.GUI;

import com.company.buisnessLayer.*;
import com.company.buisnessLayer.MenuItem;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.AreaAveragingScaleFilter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

import static com.company.buisnessLayer.Model.getUsers;

public class GenerateReports extends JFrame {
    private JPanel panel1;
    private JButton generateReport1Button;
    private JButton generateReport2Button;
    private JButton generateReport3Button;
    private JButton generateReport4Button;
    private JTextField startTextField;
    private JTextField ordNr2TextField;
    private JTextField ordNr3TextField;
    private JTextField dayTextField;
    private JTextField endTextField;
    private JTextField maxValueTextField;

    public GenerateReports(String title, DeliveryService deliveryService) {
        super(title);
        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        this.setContentPane(panel1);
        this.setLocationRelativeTo(null);
        this.setBounds(100, 100, 650, 700);
        this.setVisible(true);
        //DeliveryService deliveryService = new DeliveryService();


        generateReport1Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String file = "report1.txt";
                System.out.println(Arrays.toString(deliveryService.getOrders().toArray()));
                List<Order> stream = deliveryService.getOrders().stream()
                        .filter(order -> order.getDate().getHours() >= Integer.parseInt(startTextField.getText())
                                && order.getDate().getHours() <= Integer.parseInt(endTextField.getText()))
                        .collect(Collectors.toList());

                try {
                    ArrayList<Order> orders = (ArrayList<Order>) stream;
                    FileWriter fileWriter = new FileWriter(file);
                    fileWriter.write("Report 1 \n");
                    for(Order order : orders )
                    {
                        fileWriter.write("Order ID: " + order.getOrderId() + "\n");
                        fileWriter.write("Client ID: " + order.getClientId() + "\n\n");
                        fileWriter.write("Price: " + order.getPrice());
                        fileWriter.write("\n\nProducts: ");
                        ArrayList<MenuItem> menuItems = order.getOrder();
                        for(MenuItem m: menuItems)
                        {
                            fileWriter.write(m.getTitle()+"\n");
                        }
                        fileWriter.write("\n\n");
                    }
                    fileWriter.close();
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                }

            }
        });
        generateReport2Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                List<MenuItem> stream = deliveryService.getMenu().stream().filter(menuItem -> menuItem.getOrderNr()
                        >= Integer.parseInt(ordNr2TextField.getText()))
                        .collect(Collectors.toList());
                String file = "report2.txt";
                ArrayList<MenuItem> menuItems = (ArrayList<MenuItem>) stream;
                System.out.println(Arrays.toString(menuItems.toArray()));

                try {
                    FileWriter fileWriter = new FileWriter(file);
                    fileWriter.write("Report 2 \n");
                    fileWriter.write("Products : \n");
                    for(MenuItem menuItem : menuItems)
                        fileWriter.write(menuItem.getTitle() + " = 1 x " + menuItem.getOrderNr() + "times \n");
                    fileWriter.close();
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                }
            }
        });
        generateReport3Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int maxValue = Integer.parseInt(maxValueTextField.getText());
                int ordNr = Integer.parseInt(ordNr3TextField.getText());

                String file = "report3.txt";
                FileWriter fileWriter = null;
                try {
                    fileWriter = new FileWriter(file);

                fileWriter.write("Report 3 \n");

                List<Order> stream = deliveryService.getOrders().stream()
                        .filter(order -> order.getPrice() >= maxValue)
                        .collect(Collectors.toList());

                for(Order order : stream)
                    for(User user : getUsers()) {
                        if (user.getId() == order.getClientId()) {
                            user.incrementOrdersCount();
                            System.out.println("\n" + user.getUsername() + " " + order.getOrder().toString());
                        }
                    }

                List<User> stream1 = getUsers().stream()
                        .filter(user -> user.getOrdersCount() >= ordNr)
                        .collect(Collectors.toList());

                    for(User user : stream1) {
                        fileWriter.write("\n Username : " + user.getUsername() + " ID : " + user.getId());
                    }
                    fileWriter.close();
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                }

               // System.out.println(Arrays.toString(stream.toArray()));
            }
        });
        generateReport4Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String file = "report4.txt";
                try {
                    FileWriter fileWriter = new FileWriter(file);
                    ArrayList<MenuItem> menuItems = new ArrayList<>();
                    Integer day = Integer.parseInt(dayTextField.getText());
                    List<Order> stream = deliveryService.getOrders().stream()
                            .filter(order -> order.getDate().getDay() == day)
                            .collect(Collectors.toList());
                    for(Order order : stream)
                        menuItems.addAll(order.getOrder());
                    fileWriter.write("Report 4 \n");
                    for(MenuItem menuItem : menuItems)
                        fileWriter.write(menuItem.getTitle() + " = " + menuItem.getOrderNr() + " times \n");
                    fileWriter.close();
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                }

            }
        });
    }
}
