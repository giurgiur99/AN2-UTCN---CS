package com.company.GUI;

import com.company.DataLayer.Serializator;
import com.company.buisnessLayer.CompositeProduct;
import com.company.buisnessLayer.DeliveryService;
import com.company.buisnessLayer.MenuItem;
import com.company.buisnessLayer.Product;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashSet;

public class ManageProducts extends JFrame{
    private JPanel panel1;
    private JTabbedPane tabbedPane1;
    private JTextField titleTextField;
    private JTextField ratingTextField;
    private JTextField caloriesTextField;
    private JTextField proteinsTextField;
    private JTextField fatsTextField;
    private JTextField sodiumTextField;
    private JTextField priceTextField;
    private JButton deleteButton;
    private JComboBox<String> comboBox1;
    private JButton addButton1;
    private JButton editButton;
    private JTextField menuNameTextField;
    private JComboBox<String> selectProductsCreateMenu;
    private JButton addInMenuButton;
    private JButton doneButton;
    private JList list1;
    private  ArrayList<String> strings;
    ArrayList<Product> products;
    private ArrayList<String> customMenu;
    private ArrayList<MenuItem> menuItems;
    private int i =0;
    public ArrayList<MenuItem> a = new ArrayList<>();
    private CompositeProduct compositeProduct;

    public ManageProducts(String title, DeliveryService deliveryService)
    {
        super(title);
        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        this.setContentPane(tabbedPane1);
        this.setLocationRelativeTo(null);
        this.setBounds(100,100,800,900);
        this.setVisible(true);

        HashSet<MenuItem> menuItems = deliveryService.getMenu();
        strings = new ArrayList<>();
        for(MenuItem menuItem : menuItems)
            strings.add(menuItem.getTitle());
        System.out.println(strings);
        comboBox1.setModel(new DefaultComboBoxModel<String>(strings.toArray(new String[0])));
        selectProductsCreateMenu.setModel(new DefaultComboBoxModel<String>(strings.toArray(new String[0])));
        comboBox1.setSize(50, comboBox1.getPreferredSize().height);
        customMenu = new ArrayList<>();
        list1.setListData(customMenu.toArray());

        addButton1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                i++;
                Product product = new Product(titleTextField.getText(),
                        Double.parseDouble(ratingTextField.getText()),
                        Double.parseDouble(caloriesTextField.getText()),
                        Double.parseDouble(proteinsTextField.getText()),
                        Double.parseDouble(fatsTextField.getText()),
                        Double.parseDouble(sodiumTextField.getText()),
                        Double.parseDouble(priceTextField.getText()));
                deliveryService.addProduct(product);

            }
        });
        comboBox1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                MenuItem product = deliveryService.find(comboBox1.getItemAt(comboBox1.getSelectedIndex()));
                System.out.println(product.getTitle());
                titleTextField.setText(product.getTitle());
                ratingTextField.setText(String.valueOf(product.getRating()));
                caloriesTextField.setText(String.valueOf(product.getCalories()));
                proteinsTextField.setText(String.valueOf(product.getProteins()));
                fatsTextField.setText(String.valueOf(product.getFat()));
                sodiumTextField.setText(String.valueOf(product.getSodium()));
                priceTextField.setText(String.valueOf(product.getPrice()));

            }
        });
        editButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                MenuItem product = deliveryService.find(comboBox1.getItemAt(comboBox1.getSelectedIndex()));
                product.setTitle(titleTextField.getText());
                product.setRating(Double.parseDouble(ratingTextField.getText()));
                product.setCalories(Double.parseDouble(caloriesTextField.getText()));
                product.setProtein(Double.parseDouble(proteinsTextField.getText()));
                product.setFat(Double.parseDouble(fatsTextField.getText()));
                product.setSodium(Double.parseDouble(sodiumTextField.getText()));
                product.setPrice(Double.parseDouble(priceTextField.getText()));
                deliveryService.editProduct(product,deliveryService.find(product.getTitle()));
            }
        });
        addInMenuButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String title = products.get(selectProductsCreateMenu.getSelectedIndex()).getTitle();
                customMenu.add(title);
                a.add(deliveryService.find(title));
                list1.setListData(customMenu.toArray());

            }
        });
        doneButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                compositeProduct = new CompositeProduct(menuNameTextField.getText(), a);
                System.out.println(compositeProduct.toString());
            }
        });
    }
}
