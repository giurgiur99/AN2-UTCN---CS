package com.company.polynomials;

public class StringParse {

    public int getCoef(String p)
    {
        int plus = 1;
        int coef = 0;
        if(p.charAt(0) == 'x' || p.charAt(1) == 'x')
            coef=1;

        for(int i = 0 ; i < p.length() ; i++) {
            if(p.charAt(i) == '-')
                plus = 0;
            else if(p.charAt(i) == '+')
                plus = 1;
            else if( p.charAt(i) - '0' >= 0 && p.charAt(i) -'0'< 10 )
                coef = coef * 10 + p.charAt(i) - '0';
            else break;
        };
        if(plus==0)
            coef*=-1;

        return coef;
    }

    public int getDeg(String p)
    {
        int plus = 1;
        int deg = 0;
        int start = 0;
        for(int i = 0 ; i < p.length() ; i++) {

            if(p.charAt(i) == '^')
            {
                start = 1;
                i++;
            }
            else if(p.charAt(i)=='x' && i+1 == p.length())
            {
                deg = 1;
                break;
            }


            if(start==1) {
                if (p.charAt(i) == '-')
                    plus = 0;
                else if (p.charAt(i) == '+')
                    plus = 1;
                else if (p.charAt(i) - '0' > 0 && p.charAt(i) - '0' < 10)
                    deg = deg * 10 + p.charAt(i) - '0';
                else break;
            }
        };

        if(plus==0)
            deg*=-1;

        return deg;

    }
}
