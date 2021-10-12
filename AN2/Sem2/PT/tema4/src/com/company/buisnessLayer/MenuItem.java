package com.company.buisnessLayer;

public abstract class MenuItem {
    public abstract double getPrice();
    public abstract String getTitle();
    public abstract double getRating();
    public abstract double getCalories();
    public abstract double getProtein();
    public abstract double getFat();
    public abstract double getSodium();
    public abstract void setTitle(String param);
    public abstract void setRating(double param);
    public abstract void setCalories(double param);
    public abstract void setProtein(double param);
    public abstract void setFat(double param);
    public abstract void setSodium(double param);
    public abstract void setPrice(double param);
    public abstract boolean equals(Object o);
    public abstract int hashCode();
    public abstract int getOrderNr();
    public abstract void orderNrplus();
    public abstract double getProteins();
}
