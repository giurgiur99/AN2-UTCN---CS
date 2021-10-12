package com.company;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.awt.*;

import javax.swing.*;

public class GUI extends JFrame {
    ArrayList<String> queue_strings;
    private int numberOfClients, noOfQueues, lengthOfSimulation, minArrivingTime, maxArrivingTime, minServiceTime, maxServiceTime;
    private JFrame frame;
    private JPanel mainPanel, queueSimulationPanel, dataEnterPanel, queueDataPanel;
    private JLabel numberOfClientsLabel, noOfQueuesLabel, lengthOfSimulationLabel, minArrivingLabel, maxArrivingLabel, minServiceLabel, maxServiceLabel, nextClientLabel, simulationTimeLabel, averageTimeLabel, peakWaitingTimeLabel, peakHourLabel;
    private JTextField numberOfClientsTextField, maxServiceTextField, minServiceTextField, maxArrivingTextField, minArrivingTextField, lengthOfSimulationTextField, txtNoOfQueues = new JTextField();
    private ArrayList<JTextArea> queues;
    private Shop shop;

    public void rewriteGUI(ArrayList<String> toBePrinted, String nextClient, String simulationTime, String averageWaitingTime, String peakHour, String peakWaitingTime)
    {
        for (int i = 0; i < toBePrinted.size(); i++)
            this.queues.get(i).setText(toBePrinted.get(i));
        this.averageTimeLabel.setText(averageWaitingTime);
        this.simulationTimeLabel.setText(simulationTime);
        this.peakHourLabel.setText(peakHour);
        this.peakWaitingTimeLabel.setText(peakWaitingTime);
        this.nextClientLabel.setText(nextClient);
    }

    public GUI() {
        queue_strings = new ArrayList<String>();
        frame = new JFrame("Queues");
        mainPanel = new JPanel();
        queueSimulationPanel = new JPanel();
        dataEnterPanel = new JPanel();
        queueDataPanel = new JPanel();

        numberOfClientsLabel = new JLabel("Number of clients");
        numberOfClientsTextField = new JTextField();

        noOfQueuesLabel = new JLabel("Number of queues:");
        txtNoOfQueues = new JTextField();

        lengthOfSimulationLabel = new JLabel("Length of simulation:");
        lengthOfSimulationTextField = new JTextField();

        minArrivingLabel = new JLabel("Minimum arrival interval:");
        minArrivingTextField = new JTextField();

        maxArrivingLabel = new JLabel("Maximum arrival interval :");
        maxArrivingTextField = new JTextField();

        minServiceLabel = new JLabel("Minimum service time for clients:");
        minServiceTextField = new JTextField();

        maxServiceLabel = new JLabel("Maximum service time for clients:");
        maxServiceTextField = new JTextField();
        nextClientLabel = new JLabel();

        simulationTimeLabel = new JLabel();

        averageTimeLabel = new JLabel();
        peakWaitingTimeLabel = new JLabel();
        peakHourLabel = new JLabel();

        queues = new ArrayList<JTextArea>();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 450);
        frame.setLocationRelativeTo(null);
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
        dataEnterPanel.setLayout(new BoxLayout(dataEnterPanel, BoxLayout.Y_AXIS));
        dataEnterPanel.setAlignmentX(Component.CENTER_ALIGNMENT);

        queueDataPanel.setLayout(new BoxLayout(queueDataPanel, BoxLayout.Y_AXIS));
        queueSimulationPanel.setLayout(new BoxLayout(queueSimulationPanel, BoxLayout.X_AXIS));
        JButton btnSimulate = new JButton("Simulate");

        addFieldsToDataIn();

        dataEnterPanel.setMaximumSize(new Dimension(300, 300));
        mainPanel.add(dataEnterPanel);

        numberOfClientsTextField.setText("2");
        lengthOfSimulationTextField.setText("60");
        txtNoOfQueues.setText("3");
        minArrivingTextField.setText("5");
        maxArrivingTextField.setText("10");
        minServiceTextField.setText("5");
        maxServiceTextField.setText("10");

        queueDataPanel.add(peakWaitingTimeLabel);
        queueDataPanel.add(peakHourLabel);
        queueDataPanel.add(averageTimeLabel);

        GUI thisGUI = this;
        btnSimulate.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                frame.setSize(1400, 500);
                setupQueues();
                btnSimulate.setVisible(false);
                dataEnterPanel.setVisible(false);
                dataEnterPanel.revalidate();
                for (int i = 0; i < noOfQueues; i++) {
                    JTextArea ta = new JTextArea("queue");
                    queues.add(ta);
                    ta.setMaximumSize(new Dimension((1400 / noOfQueues), 300));
                    queueSimulationPanel.add(ta);
                    queueSimulationPanel.revalidate();
                }
                numberOfClients = Integer.parseInt(numberOfClientsTextField.getText());
                mainPanel.revalidate();
                shop = new Shop(numberOfClients, lengthOfSimulation, minArrivingTime, maxArrivingTime, minServiceTime, maxServiceTime, noOfQueues, queue_strings, thisGUI);
                try {
                    shop.startSimulation();
                } catch (InterruptedException e1) {
                    e1.printStackTrace();
                }

            }
        });

        mainPanel.add(btnSimulate);
        mainPanel.add(nextClientLabel);
        mainPanel.add(simulationTimeLabel);
        mainPanel.add(queueSimulationPanel);
        mainPanel.add(queueDataPanel);
        frame.add(mainPanel);
        frame.setVisible(true);
    }

    private void addFieldsToDataIn() {

        dataEnterPanel.add(numberOfClientsLabel);
        dataEnterPanel.add(numberOfClientsTextField);
        dataEnterPanel.add(lengthOfSimulationLabel);
        dataEnterPanel.add(lengthOfSimulationTextField);
        dataEnterPanel.add(noOfQueuesLabel);
        dataEnterPanel.add(txtNoOfQueues);
        dataEnterPanel.add(minArrivingLabel);
        dataEnterPanel.add(minArrivingTextField);
        dataEnterPanel.add(maxArrivingLabel);
        dataEnterPanel.add(maxArrivingTextField);
        dataEnterPanel.add(minServiceLabel);
        dataEnterPanel.add(minServiceTextField);
        dataEnterPanel.add(maxServiceLabel);
        dataEnterPanel.add(maxServiceTextField);

    }

    public void setupQueues() {
        noOfQueues = Integer.parseInt(txtNoOfQueues.getText());
        lengthOfSimulation = Integer.parseInt(lengthOfSimulationTextField.getText());
        minArrivingTime = Integer.parseInt(minArrivingTextField.getText());
        maxArrivingTime = Integer.parseInt(maxArrivingTextField.getText());
        minServiceTime = Integer.parseInt(minServiceTextField.getText());
        maxServiceTime = Integer.parseInt(maxServiceTextField.getText());
    }

}
