public class Derivative extends Asset{
    private int leva;
    private static int maxLeva;
    private final boolean shortSell;
    public Derivative(String n, double p, double sp, int u, int l, boolean ss) {
        super(n,p,sp,u);
        shortSell = ss;
        leva = l;
        maxLeva = 400;
        if(leva < 1)
            leva = 1;
        else
          if(leva > maxLeva)
            leva = maxLeva;
    }
    public final double totalGain() {
        if(getPrice()!=getSellPrice()) {
            double investimento = getPrice() * getUnit();
            double prestito = (investimento * leva) - investimento;
            double ris = (getSellPrice() * getUnit() * leva) - (investimento + prestito);
            if(shortSell)
              ris *= -1;
            if(getTaxOn() && (ris > 0))
              return (ris - (ris * getTassa()));
            return ris;
        }
        return 0;
    }
    public final double gain(int u) {
        return totalGain();
    }
    public final boolean uguale(Asset pd) {
        if(pd instanceof Derivative) {
            Derivative d = (Derivative)pd;
            return ((getName() == d.getName()) && (getPrice() == d.getPrice()) && 
                    (getSellPrice() == d.getSellPrice()) && 
                    (leva == d.leva) && (shortSell == d.shortSell));
        }
        return false;
    }
    public final boolean getShort() {
        return shortSell;
    }
    public final int getLeva() {
        return leva;
    }
    public final Asset unionAsset(Asset a) {
        Derivative da = (Derivative)this;
        Derivative db = (Derivative)a;
        int newUnit = da.getUnit() + db.getUnit();
        double newPrice = (da.getPrice()*da.getUnit() + db.getPrice()*db.getUnit()) / newUnit;
        double newSellPrice = (da.getSellPrice()*da.getUnit() + db.getSellPrice()*db.getUnit()) / newUnit;
        return new Derivative(da.getName(), newPrice, newSellPrice, newUnit, da.getLeva(), da.getShort());
    }
}