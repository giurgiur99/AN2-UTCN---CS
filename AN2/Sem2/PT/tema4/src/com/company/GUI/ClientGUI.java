package com.company.GUI;

import com.company.buisnessLayer.*;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;

public class ClientGUI extends JFrame{
    private JTabbedPane tabbedPane1;
    private JPanel panel1;
    private JTextField searchTitle;
    private JTextField searchRaintg;
    private JTextField searchCalories;
    private JTextField searchProteins;
    private JTextField searchPrice;
    private JButton searchButton;
    private JList list1;
    private JComboBox comboBox1;
    private JList list2;
    private JButton placeOrderButton;
    private JButton addToOrderButton;
    private JTextField searchFats;
    private JLabel Proteins;
    private JTextField searchSodium;
    //DeliveryService deliveryService = new DeliveryService();
    public ArrayList<MenuItem> a = new ArrayList<>();
    static int userId;
    public static final String ORDER = "Order";

    public ClientGUI(String title, DeliveryService deliveryService)
    {
        super(title);
        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        this.setContentPane(panel1);
        this.setLocationRelativeTo(null);
        this.setBounds(100,100,900,750);
        this.setVisible(true);
        ArrayList<String> customMenu = new ArrayList<>();
        ArrayList<Product> products = deliveryService.importBaseProducts();
        ArrayList<String> strings = new ArrayList<>();
        for(Product product : products)
            strings.add(product.getTitle());
        System.out.println(strings);
        comboBox1.setModel(new DefaultComboBoxModel<String>(strings.toArray(new String[0])));

        comboBox1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

            }
        });
        placeOrderButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println(a.toString());
                
                String oldValue = null;
                String newValue = deliveryService.addOrder(a,userId).getStringOrder();
                firePropertyChange(ORDER,oldValue,newValue);
                oldValue = newValue;
                list2.setModel(new DefaultListModel());
                a.clear();
                customMenu.clear();

                //firePropertyChange(ORDER,"a",);

            }
        });
        addToOrderButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String title = products.get(comboBox1.getSelectedIndex()).getTitle();
                customMenu.add(title);
                a.add(deliveryService.find(title));
                deliveryService.find(title).orderNrplus();
                list2.setListData(customMenu.toArray());
            }
        });
        searchButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                List<MenuItem> men = deliveryService.search(searchTitle.getText(),
                        searchRaintg.getText(),
                        searchCalories.getText(),
                        searchProteins.getText(),
                        searchFats.getText(),
                        searchSodium.getText(),
                        searchPrice.getText());
                System.out.println(Arrays.toString(men.toArray()));

                list1.setListData(men.toArray());
            }
        });
    }


    public static void setUserId(int id) {
        userId = id;
    }
}
