package com.company.GUI;

import com.company.buisnessLayer.DeliveryService;
import com.company.buisnessLayer.MenuItem;
import com.company.buisnessLayer.Product;
import com.company.buisnessLayer.AdminManager;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileNotFoundException;
import java.util.ArrayList;

public class AdminGUI extends JFrame{
    private JPanel panel1;
    private JButton importDATAButton;
    private JButton manageProductsButton;
    private JButton generateReportsButton;
    ArrayList<Product> products;

    public AdminGUI(String title, DeliveryService deliveryService) throws FileNotFoundException {
        super(title);
        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        this.setContentPane(panel1);
        this.setLocationRelativeTo(null);
        this.setBounds(100,100,450,550);
        this.setVisible(true);
        AdminManager adminManager = new AdminManager();
        //DeliveryService deliveryService = new DeliveryService();

        importDATAButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ArrayList<Product> products = new ArrayList<>();
                products = deliveryService.importBaseProducts();
                System.out.println(deliveryService.getMenu().size());
                JOptionPane.showMessageDialog(null, "Data is loaded");
            }
        });


        manageProductsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFrame manageProducts = new ManageProducts("Manage products", deliveryService);
            }
        });

        generateReportsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                GenerateReports generateReports = new GenerateReports("Generate reports", deliveryService);
            }
        });
    }
}
