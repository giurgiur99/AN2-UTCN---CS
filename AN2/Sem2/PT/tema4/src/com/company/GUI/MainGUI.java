package com.company.GUI;

import com.company.DataLayer.Serializator;
import com.company.buisnessLayer.*;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.*;
import java.util.*;

public class MainGUI extends JFrame implements Serializable{
    private JPanel panel1;
    private JTextField usernameTextField;
    private JTextField passwordTextField;
    private JButton signInButton;
    private Role role;
    private String username;
    private String password;
    private ArrayList<User> users;
    private boolean createNewClient = true;
    public HashSet<Order> orderHashSet = new HashSet<>();
    DeliveryService deliveryService = new DeliveryService();

    public MainGUI(String title) throws IOException {
        super(title);
        Serializator.deserialization();

        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setContentPane(panel1);
        this.setLocationRelativeTo(null);
        this.setBounds(100,100,400,500);
        this.setVisible(true);
        users = new ArrayList<>();
        Scanner scanner = new Scanner(new File("login.txt"));
        while(scanner.hasNextLine())
        {
            Scanner scanner2 = new Scanner(scanner.nextLine());
            scanner2.useDelimiter(",");
            Role role1 = Role.valueOf(scanner2.next());
            String username = scanner2.next();
            String password = scanner2.next();
            User user = new User(username, password, role1);
            //System.out.println(user.toString());
            users.add(user);
        }
        scanner.close();
        Model.setUsers(users);
        FileWriter writer = new FileWriter("login.txt", true);
        JFrame adminGUI = new AdminGUI("Admin GUI",deliveryService);
        adminGUI.setVisible(false);
        JFrame clientGUI = new ClientGUI("Client GUI",deliveryService);
        clientGUI.setVisible(false);
        JFrame employeeGUI = new EmployeeGUI("Employee GUI",clientGUI,deliveryService);
        employeeGUI.setVisible(false);
        //deliveryService.addObs((Observer) employeeGUI);

        signInButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                role = Role.Client;
                username = usernameTextField.getText();
                password = passwordTextField.getText();
                System.out.println(username);
                for(User user : users)
                    if(user.getUsername().equals(username)) {
                        System.out.println("ok1");
                        role = user.getRole();
                        createNewClient = false;
                        if (role == Role.Admin)
                            adminGUI.setVisible(true);
                        if (role == Role.Client)
                        {
                            clientGUI.setVisible(true);
                            ClientGUI.setUserId(user.getId());
                        }

                        if(role == Role.Employee)
                            employeeGUI.setVisible(true);

                    }
                if (createNewClient)
                {
                    User user = new User(username, password,role);
                    clientGUI.setVisible(true);
                    try {
                        writer.write("\n" + role.toString() + "," + username + "," + password );
                    } catch (IOException ioException) {
                        ioException.printStackTrace();
                    }
                    try {
                        writer.close();
                    } catch (IOException ioException) {
                        ioException.printStackTrace();
                    }
                    users.add(user);
                    Model.setUsers(users);
                }

            }
        });
    }


}
