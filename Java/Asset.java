public abstract class Asset {
    private final String name;
    private final double price;
    private final double sellPrice;
    private static boolean taxOn;
    private static double tassa;
    private final int unit;
    
    public Asset(String n, double p, double sp, int u) {
        name = n;
        price = p;
        sellPrice = sp;
        unit = u;
        tassa = 0.26;
        taxOn = false;
    }
    public final double getPrice() {
        return price;
    }
    public final double getSellPrice() {
        return sellPrice;
    }
    public final int getUnit() {
        return unit;
    }
    public static final boolean getTaxOn() {
        return taxOn;
    }
    public static final void setTaxOn(boolean b) {
        if(taxOn != b)
            taxOn = b;
    }
    public final String getName() {
        return name;
    }
    public final double getInvestimento() {
        return price*unit;
    }
    public final static double getTassa() {
        return tassa;
    } 
    public abstract double gain(int u);
    public abstract double totalGain();
    public double roi() {
        return ((totalGain()/getInvestimento())*100);
    }
    public final double diffgain(Asset a) {
        return (((a.roi())-roi())/roi())*100;
    }
    double add(Asset a) { //operator+
        return (totalGain()+a.totalGain());
    }
    public abstract boolean uguale(Asset a);
    public static final double add(double d, Asset a) {
        return (d + a.totalGain());
    }
    public abstract Asset unionAsset(Asset a);
}