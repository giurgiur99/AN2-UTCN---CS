package com.company.buisnessLayer;

import java.io.Serializable;
import java.util.Objects;

public class Product extends MenuItem implements Serializable {
    private String title;
    private double rating;
    private double calories;
    private double protein;
    private double fat;
    private double sodium;
    private double price;
    public int orderNr = 0;

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
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
        return protein;
    }

    @Override
    public double getFat() {
        return fat;
    }

    public void setCalories(double calories) {
        this.calories = calories;
    }

    @Override
    public void setProtein(double protein) {
        this.protein = protein;
    }

    @Override
    public void setFat(double fat) {
        this.fat = fat;
    }

    public double getProteins() {
        return protein;
    }

    public void setProteins(double protein) {
        this.protein = protein;
    }

    public double getFats() {
        return fat;
    }

    public void setFats(double fat) {
        this.fat = fat;
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

    @Override
    public boolean equals(Object o) {
        if (((Product) o).getTitle().equals(this.getTitle()))
            return true;

        return false;
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.title);

    }

    @Override
    public int getOrderNr() {
        return orderNr;
    }

    @Override
    public void orderNrplus() {
        this.orderNr++;

    }

    public Product(String title, double rating, double calories, double proteins, double fats, double sodium, double price) {
        this.title = title;
        this.rating = rating;
        this.calories = calories;
        this.protein = proteins;
        this.fat = fats;
        this.sodium = sodium;
        this.price = price;
    }

    @Override
    public String toString() {
        return "Product{" +
                "title='" + title + '\'' +
                ", rating=" + rating +
                ", calories=" + calories +
                ", proteins=" + protein +
                ", fats=" + fat +
                ", sodium=" + sodium +
                ", price=" + price +
                '}';
    }
}
