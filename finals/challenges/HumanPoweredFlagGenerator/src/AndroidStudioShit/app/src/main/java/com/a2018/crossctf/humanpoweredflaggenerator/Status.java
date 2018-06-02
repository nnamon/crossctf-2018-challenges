package com.a2018.crossctf.humanpoweredflaggenerator;

import android.annotation.SuppressLint;

import java.math.BigInteger;
import java.text.DecimalFormat;

class Status {
    private int level;
    private BigInteger max;
    private BigInteger curr;
    private BigInteger prod;
    private BigInteger fmax;
    private BigInteger f;
    private StringBuilder flagBuilder;

    Status() {
        this.level = 0;
        this.flagBuilder = new StringBuilder();
        upLevel();
    }

    // CRANK!
    public void crank(double am) {
        double amount = Math.pow(am, level);
        for (int i = 0; i < amount; ++i) {
            if (this.max.compareTo(this.curr) == 0) {
                if (this.level == 13) {
                    return;
                }

                this.flagBuilder.append(extract());
                upLevel();
            } else if (this.f.compareTo(this.fmax) == 0) {
                this.curr = this.curr.add(BigInteger.ONE);
                upF();
            } else {
                this.prod = this.prod.multiply(f);
                this.f = this.f.add(BigInteger.ONE);
            }
        }
    }

    public String flag() {
        return flagBuilder.toString();
    }

    public int level() {
        return level;
    }

    @SuppressLint("DefaultLocale")
    public String percent() {
        double frac = BigInteger.valueOf(10000).divide(this.max.subtract(BigInteger.ONE)).doubleValue();
        double x = this.curr.doubleValue() - 1;
        double y = BigInteger.valueOf(10000).multiply(this.f).divide(this.fmax).doubleValue();

        return String.format("%.2f", Math.min(100, frac * (x + y / 10000) / 100));
    }

    private void upLevel() {
        ++this.level;
        this.max = BigInteger.ONE.shiftLeft(this.level).add(BigInteger.ONE);
        this.curr = BigInteger.ONE;
        this.prod = BigInteger.ONE;
        upF();
    }

    private void upF() {
        this.fmax = fastExpo(BigInteger.valueOf(5), this.curr).add(BigInteger.ONE);
        this.f = BigInteger.ONE;
    }

    public void speedUp() {
        while ((this.prod.mod(BigInteger.TEN).compareTo(BigInteger.ZERO)) == 0) {
            this.prod = this.prod.divide(BigInteger.TEN);
        }
    }

    private String extract() {
        BigInteger thousand = BigInteger.valueOf(1000L);
        speedUp();
        return this.prod.mod(thousand).add(thousand).toString().substring(1);
    }

    private static BigInteger fastExpo(BigInteger x, BigInteger y) {
        BigInteger out = BigInteger.ONE;
        while (y.compareTo(BigInteger.ONE) != 0) {
            if (y.and(BigInteger.ONE).compareTo(BigInteger.ONE) == 0) {
                out = out.multiply(x);
            }
            x = x.multiply(x);
            y = y.shiftRight(1);
        }
        return out.multiply(x);
    }
}