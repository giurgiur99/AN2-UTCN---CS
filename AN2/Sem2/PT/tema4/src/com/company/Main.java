package com.company;

import com.company.GUI.AdminGUI;
import com.company.GUI.ClientGUI;
import com.company.GUI.MainGUI;
import com.company.GUI.ManageProducts;
import com.company.buisnessLayer.AdminManager;

import javax.swing.*;
import java.io.FileNotFoundException;
import java.io.IOException;

public class Main {

    public static void main(String[] args) throws IOException {
        JFrame mainGUI = new MainGUI("Client");
        //AdminManager manager = new AdminManager();
        //System.out.println(manager.readCsv());

    }
}
