package com.company.buisnessLayer;

import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class AdminManager {

        public ArrayList<Product> readCsv () throws FileNotFoundException {
            Scanner sc = new Scanner(new File( "products.csv"));
            ArrayList<Product> products = new ArrayList<>();
            int i = 0;
            sc.useDelimiter(" ");   //sets the delimiter pattern
            sc.nextLine();
            while (sc.hasNextLine())  //returns a boolean value
            {
                Scanner sc2 = new Scanner(sc.nextLine());
                sc2.useDelimiter(",");
                Product product = new Product(sc2.next(),Double.parseDouble(sc2.next()),Double.parseDouble(sc2.next()),Double.parseDouble(sc2.next()),Double.parseDouble(sc2.next()),Double.parseDouble(sc2.next()),Double.parseDouble(sc2.next()));
                //System.out.println(product.toString());
                products.add(product);
            }
            sc.close();  //closes the scanner
            return products;
        }

}
