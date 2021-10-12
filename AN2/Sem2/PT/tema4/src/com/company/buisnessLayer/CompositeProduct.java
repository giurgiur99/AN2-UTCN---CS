package com.company.buisnessLayer;

import java.util.ArrayList;
import java.util.Objects;

public class CompositeProduct extends MenuItem {
    private String title;
    private double rating;
    private double calories;
    private double proteins;
    private double fats;
    private double sodium;
    private double price;
    private int orderNr = 0;
    private ArrayList<MenuItem> products;
    private int oderId = 0;

    public CompositeProduct(String title, ArrayList<MenuItem> products){
        this.title = title;
        this.products = products;
        for(MenuItem menuItem : products)
        {
            this.rating = menuItem.getRating() + this.rating;
            this.calories = menuItem.getCalories() + this.calories;
            this.proteins = menuItem.getProteins() + this.proteins;
            this.fats = menuItem.getFat() + this.fats;
            this.sodium = menuItem.getSodium() + this.sodium;
            this.price = menuItem.getPrice() + this.price;
        }
        this.rating = this.rating / products.size();
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }




    @Override
    public boolean equals(Object o) {
        return false;
    }

    public double getRating() {
        return rating;
    }

    public void setRating(double rating) {
        this.rating = rating;
    }

    public double getCalories() {
        return calories;
    }

    @Override
    public double getProtein() {
        return proteins;
    }

    @Override
    public double getFat() {
        return fats;
    }

    public void setCalories(double calories) {
        this.calories = calories;
    }

    @Override
    public void setProtein(double proteins) {
        this.proteins = proteins;
    }

    @Override
    public void setFat(double fat) {
        this.fats = fat;
    }

    public double getProteins() {
        return proteins;
    }

    public void setProteins(double proteins) {
        this.proteins = proteins;
    }

    public double getFats() {
        return fats;
    }

    public void setFats(double fats) {
        this.fats = fats;
    }

    public double getSodium() {
        return sodium;
    }

    public void setSodium(double sodium) {
        this.sodium = sodium;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public ArrayList<MenuItem> getProducts() {
        return products;
    }

    public void setProducts(ArrayList<MenuItem> products) {
        this.products = products;
    }

    public int getOderId() {
        return oderId;
    }

    public void setOderId(int oderId) {
        this.oderId = oderId;
    }

    public int hashCode(){
        return Objects.hash(this.title);
    }

    @Override
    public int getOrderNr() {
        return this.orderNr;
    }

    @Override
    public void orderNrplus() {
        this.orderNr++;

    }

    @Override
    public String toString() {
        return "CompositeProduct{" +
                "title='" + title + '\'' +
                ", rating=" + rating +
                ", calories=" + calories +
                ", proteins=" + proteins +
                ", fats=" + fats +
                ", sodium=" + sodium +
                ", price=" + price +
                ", products=" + products +
                ", oderId=" + oderId +
                '}';
    }
}
