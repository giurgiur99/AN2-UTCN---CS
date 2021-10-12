package com.company;

import com.company.polynomials.Monomial;
import com.company.polynomials.Polynomial;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GUI  extends JFrame {

    private JPanel panel1;
    private JButton ADDButton;
    private JButton SUBSTRACTButton;
    private JButton DIVIDEButton;
    private JButton MULTIPLYButton;
    private JButton INTEGRATEButton;
    private JButton DERIVATEButton;
    private JTextField resultPolynomial;
    private JTextField secondPolynomial;
    private JTextField firstPolynomial;

    public GUI(String title)
    {
        super(title);
         this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
         this.setContentPane(panel1);
         this.setSize(450,500);
         this.setLocationRelativeTo(null);
         this.setVisible(true);


        ADDButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //System.out.println(firstPolynomial.getText());
                Polynomial polynomial1 = new Polynomial(firstPolynomial.getText());
                Polynomial polynomial2 = new Polynomial(secondPolynomial.getText());
                resultPolynomial.setText(polynomial1.addition(polynomial2).PolynomialToString());
            }
        });
        SUBSTRACTButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Polynomial polynomial1 = new Polynomial(firstPolynomial.getText());
                Polynomial polynomial2 = new Polynomial(secondPolynomial.getText());
                resultPolynomial.setText(polynomial1.substraction(polynomial2).PolynomialToString());
            }
        });
        MULTIPLYButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Polynomial polynomial1 = new Polynomial(firstPolynomial.getText());
                Polynomial polynomial2 = new Polynomial(secondPolynomial.getText());
                resultPolynomial.setText(polynomial1.multiply(polynomial2).PolynomialToString());
            }
        });
        DIVIDEButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Polynomial polynomial1 = new Polynomial(firstPolynomial.getText());
                Polynomial polynomial2 = new Polynomial(secondPolynomial.getText());
                resultPolynomial.setText(polynomial1.divide(polynomial2).PolynomialToString());
            }
        });
        DERIVATEButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Polynomial polynomial1 = new Polynomial(firstPolynomial.getText());
                resultPolynomial.setText(polynomial1.differentiate(polynomial1).PolynomialToString());
            }
        });
        INTEGRATEButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Polynomial polynomial1 = new Polynomial(firstPolynomial.getText());
                resultPolynomial.setText(polynomial1.integrate(polynomial1).PolynomialToString());
            }
        });
    }


}
