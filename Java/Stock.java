public class Stock extends Asset {
    private final double dividendo;
    public Stock(String n, double p, double sp, int u, double d){
        super(n,p,sp,u);
        dividendo = d;
    }
    public final double gain(int sellUnit) {
        if(sellUnit > 0) {
            if(sellUnit > getUnit())
                sellUnit = getUnit();
            double ris = (getSellPrice() - getPrice()) * sellUnit;
            if(getTaxOn() && (ris > 0))
                return (ris - ris*getTassa());
            return ris;
        }
        return 0;
    }
    public final double gainDividendo() {
        double ris = getUnit() * dividendo;
        if(getTaxOn())
            return (ris - ris * getTassa());
        return ris;
    }
    public final double totalGain() {
        return (gain(getUnit()) + gainDividendo());
    }
    public final boolean uguale(Asset ps){
        if(ps instanceof Stock){
            Stock s = (Stock)ps;
            return ((getName().equals(s.getName())) && (getPrice() == s.getPrice()) && 
                    (getSellPrice() == s.getSellPrice()) && (dividendo == s.dividendo));
        }
    return false;
    }
    public final Asset unionAsset(Asset a) {
        Stock sa = (Stock)this;
        Stock sb = (Stock)a;
        int newUnit = sa.getUnit() + sb.getUnit();
        double newPrice = (sa.getPrice()*sa.getUnit() + sb.getPrice()*sb.getUnit()) / newUnit;
        double newSellPrice = (sa.getSellPrice()*sa.getUnit() + sb.getSellPrice()*sb.getUnit()) / newUnit;
        double newDividend = (sa.dividendo*sa.getUnit() + sb.dividendo*sb.getUnit()) / newUnit;
        return new Stock(sa.getName(), newPrice, newSellPrice, newUnit, newDividend);
    }
}
