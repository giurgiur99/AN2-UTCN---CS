package com.company.buisnessLayer;

import java.util.ArrayList;

public class Model {
    private static ArrayList<User> users = new ArrayList<>();

    public void addUser(User u){
        users.add(u);
    }

    public static ArrayList<User> getUsers() {
        return users;
    }

    public static void setUsers(ArrayList<User> users1) {
      users = users1;
    }

    public static int getUserID(String username, String password){
        for(User user: users){
            if(user.getUsername().equals(username)){
                return user.getId();
            }
        }
        return -1;
    }
}
