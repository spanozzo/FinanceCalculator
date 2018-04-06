public class Bond extends Asset {
    private final double coupon;
    private final boolean stato;
    private static double tassaStato;
    public Bond(String n, double p, double sp, int u, double c, boolean s){
        super(n,p,sp,u);
        coupon = c;
        stato = s;
        tassaStato = 0.125;
    }
    public final double gain(int unit) {
        double ris = (getSellPrice() - getPrice()) * unit;
        if(getTaxOn() && (ris > 0)) {
          if(stato)
            return (ris - ris * tassaStato);
          return (ris - ris * getTassa());
        }
        return ris;
    }
    public final double gainCedola() {
        double ris = (getInvestimento() * coupon) / 100;
        if(getTaxOn()) {
          if(stato)
            return (ris - ris * tassaStato);
          else
            return (ris - ris * getTassa());
        }
        return ris;
    }
    public final double totalGain() {
        return (gain(getUnit()) + gainCedola());
    }
    public final boolean uguale(Asset pb) {
        if(pb instanceof Bond) {
            Bond b = (Bond)pb;
            return ((getName() == b.getName()) && (getPrice() == b.getPrice()) && 
                    (getSellPrice() == b.getSellPrice()) &&
                    (coupon == b.coupon) && (stato == b.stato));
          }
          return false;
    }
    public final double getCoupon() {
        return coupon;
    }
    public final boolean getStato() {
        return stato;
    }
    public final Asset unionAsset(Asset a) {
        Bond ba = (Bond)this;
        Bond bb = (Bond)a;
        int newUnit = ba.getUnit() + bb.getUnit();
        double newPrice = (ba.getPrice()*ba.getUnit() + bb.getPrice()*bb.getUnit()) / newUnit;
        double newSellPrice = (ba.getSellPrice()*ba.getUnit() + bb.getSellPrice()*bb.getUnit()) / newUnit;
        double newCoupon = (ba.getInvestimento()*ba.getCoupon() + bb.getInvestimento()*bb.getCoupon()) / (ba.getInvestimento()+bb.getInvestimento());
        return new Bond(ba.getName(), newPrice, newSellPrice, newUnit, newCoupon, ba.getStato());
    }
}
