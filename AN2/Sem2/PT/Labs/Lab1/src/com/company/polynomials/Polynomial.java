package com.company.polynomials;

import java.util.ArrayList;
import java.util.Scanner;
import java.lang.String;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Polynomial extends StringParse {

    private ArrayList<Monomial> elements;
    public Polynomial()
    {
        elements = new ArrayList<Monomial>();
    }

    public Polynomial(Polynomial p)
    {
        elements = new ArrayList<Monomial>();
        for(Monomial m:p.elements)
        {
            if(m.getCoefficient().doubleValue()%1==0)
                this.elements.add(new IntegerMonomial(m.getCoefficient().intValue(),m.getDegree()));
            else
                this.elements.add(new RealMonomial(m.getCoefficient().doubleValue(),m.getDegree()));
        }
    }

    public Polynomial(String P)
    {
        elements = new ArrayList<Monomial>();
        //String exp = "2x^3-42x^2+5x-26";
        Pattern pattern = Pattern.compile("([+-]?[^-+]+)");
        Matcher matcher = pattern.matcher(P);
        int x=0;
        int plus = 1;
        int deg = 0;
        while (matcher.find()) {
            x=x+1;
            System.out.println("Group "+x+": " + matcher.group(1));
            Monomial monomial = new IntegerMonomial(getCoef(matcher.group(1)),getDeg(matcher.group(1)));
            this.elements.add(monomial);
            System.out.println(getCoef(matcher.group(1)) + "   " + getDeg(matcher.group(1)));
        }

    }

    public Polynomial addition(Polynomial p)
    {
        for(Monomial m : p.elements)
        {
            int ok = 0;
            for(Monomial m1:this.elements)
                if(m.getDegree() == m1.getDegree())
                {
                    ok = 1;
                    m1.add(m);
                    break;
                }
            if(ok==0)
                this.elements.add(m);
        }
        return this;
    }

    public Polynomial substraction(Polynomial p)
    {
        for(Monomial m:p.elements)
        {
            int ok = 0;
            Monomial m2 = m;
            for(Monomial m1:this.elements)
                if(m.getDegree() == m1.getDegree())
                {
                    ok = 1;
                    m1.subtract(m);
                    m2  = m1;
                    break;
                }
                if(ok == 0)
                    this.elements.add(m);
                else
                    if(m2.getCoefficient().doubleValue()==0)
                        this.elements.remove(m2);
        }
        return this;
    }

    public Polynomial multiply(Polynomial p)
    {
        Polynomial prod = new Polynomial();
        for(Monomial m:this.elements)
        {
            for(Monomial m1:p.elements) {
                Monomial res = new IntegerMonomial(m.getCoefficient().intValue() * m1.getCoefficient().intValue(),m.getDegree() + m1.getDegree());
                Polynomial p1 = new Polynomial();
                p1.elements.add(res);
                prod.addition(p1);
            }
        }
        return prod;
    }

    public Polynomial divide(Polynomial p) {
        this.elements.sort((m1, m2)-> (Integer.compare(m2.getDegree(), m1.getDegree())));
        p.elements.sort((m1, m2)-> (Integer.compare(m2.getDegree(), m1.getDegree())));
        Polynomial quotient=new Polynomial();

        while (this.elements.size() > 0 && this.elements.get(0).getDegree() >= p.elements.get(0).getDegree())
        {
            double c1 = this.elements.get(0).getCoefficient().doubleValue();
            double c2 = p.elements.get(0).getCoefficient().doubleValue();
            Polynomial aux = new Polynomial();
            for(Monomial m:p.elements)
                aux.elements.add(new RealMonomial(m.getCoefficient().doubleValue()*((double)c1 / c2),m.getDegree()));

            RealMonomial t=new RealMonomial((double)c1/c2,this.elements.get(0).getDegree() - p.elements.get(0).getDegree());
            quotient.elements.add(t);
            for(Monomial m:aux.elements)
                m.setDegree(t.getDegree()+m.getDegree());

            this.substraction(aux);
        }
        return quotient;
    }

    public Polynomial differentiate(Polynomial p)
    {
        Polynomial aux = new Polynomial();
        int i = 0;
        for(Monomial m : p.elements) {
            m = new IntegerMonomial(p.elements.get(i).getDegree()*p.elements.get(i).getCoefficient().intValue(), p.elements.get(i).getDegree()-1);
            System.out.println(m.getCoefficient()+"x"+m.getDegree() + "+");
            aux.elements.add(m);
            i++;
        }
        return aux;
    }

    public Polynomial integrate (Polynomial p)
    {
        Polynomial aux = new Polynomial();
        int i = 0;
        for(Monomial m : p.elements) {
            if(m.getCoefficient().doubleValue()/m.getDegree() % 1 == 0)
                aux.elements.add(new IntegerMonomial(m.getCoefficient().intValue()/(m.getDegree()+1), m.getDegree()+1));
            else
                aux.elements.add(new RealMonomial(m.getCoefficient().doubleValue()/(m.getDegree()+1), m.getDegree()+1));
        }
        return aux;
    }

    public Polynomial(ArrayList<Monomial> e)
    {
        this.elements =e;
    }

    public String PolynomialToString()
    {
        this.elements.sort((m1, m2)-> (new Integer(m2.getDegree()).compareTo(m1.getDegree())));
        StringBuilder ResPolynomial=new StringBuilder();
        for(Monomial m : this.elements)
        {
            if(!m.getCoefficient().equals(0))
            {
                if(m.getCoefficient().doubleValue()%1!=0)
                {
                    if(m.getCoefficient().doubleValue()>0)
                        ResPolynomial.append("+");
                    if(m.getCoefficient().doubleValue()!=0 && m.getDegree()>1)
                        ResPolynomial.append(m.getCoefficient().toString() + "x^" + m.getDegree());
                    else
                    if(m.getCoefficient().doubleValue()!=0 && m.getDegree()==1)
                        ResPolynomial.append(m.getCoefficient().toString() + "x");
                    else
                    if(m.getCoefficient().doubleValue()!=0 && m.getDegree()==0)
                        ResPolynomial.append(m.getCoefficient().toString());
                }
                if(m.getCoefficient().doubleValue()%1==0)
                {
                    if(m.getCoefficient().intValue()>0)
                        ResPolynomial.append(" + ");
                    if(m.getCoefficient().intValue()!=0 && m.getDegree()>1)
                        ResPolynomial.append(m.getCoefficient().toString() + "x^" + m.getDegree());
                    else
                    if(m.getCoefficient().intValue()!=0 && m.getDegree()==1)
                        ResPolynomial.append(m.getCoefficient().toString() + "x");
                    else
                    if(m.getCoefficient().intValue()!=0 && m.getDegree()==0)
                        ResPolynomial.append(m.getCoefficient().toString());
                }
            }

        }
        System.out.println(ResPolynomial.toString());
        if(ResPolynomial.length()==0)
            return "0";
        return ResPolynomial.toString();
    }

}
