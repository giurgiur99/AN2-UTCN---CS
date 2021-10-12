package com.company.buisnessLayer;

import java.io.Serializable;

public class User implements Serializable {
    private String username;
    private String password;
    private Role role;
    private static int counter = 1;
    private int id = 0;
    private int ordersCount;

    public User(String username, String password, Role role){
        this.username = username;
        this.password = password;
        this.role = role;
        for(User user : Model.getUsers())
            if(username.equals(user.getUsername())) {
                id = user.getId();
                return;
            }

                if (this.role == Role.Admin) {
                    this.id = 1;
                } else {
                    counter++;
                    this.id = counter;
                }

        this.ordersCount = 0;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public Role getRole() {
        return role;
    }

    public void setRole(Role role) {
        this.role = role;
    }

    public static int getCounter() {
        return counter;
    }

    public static void setCounter(int counter) {
        User.counter = counter;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getOrdersCount() {
        return ordersCount;
    }

    public void incrementOrdersCount() {
        this.ordersCount++;
    }
}
