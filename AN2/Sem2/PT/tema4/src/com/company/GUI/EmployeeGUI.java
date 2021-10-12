package com.company.GUI;

import com.company.buisnessLayer.DeliveryService;
import com.company.buisnessLayer.MenuItem;
import com.company.buisnessLayer.Order;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.HashSet;

public class EmployeeGUI extends JFrame {
    private JPanel panel1;
    private JButton serializeBtn;
    private JComboBox comboBox;
    private JLabel orderLabel;
   // DeliveryService deliveryService = new DeliveryService();
    private int orderNr = 0;
    private static HashSet<MenuItem> menu;
    private static HashSet<Order> orders;
    public EmployeeGUI(String title, JFrame clientGUI, DeliveryService deliveryService) {
        super(title);
        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        this.setContentPane(panel1);
        this.setLocationRelativeTo(null);
        this.setBounds(100,100,490,550);
        this.setVisible(true);

        clientGUI.addPropertyChangeListener(new PropertyChangeListener() {
            @Override
            public void propertyChange(PropertyChangeEvent evt) {
                if(evt.getPropertyName().equals(ClientGUI.ORDER)) {
                    String string = evt.getNewValue().toString();
                    System.out.println(string);
                    comboBox.addItem(string);
                }
            }
        });
        serializeBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                deliveryService.storeInfo();
            }
        });

    }



}
