import java.util.Vector;

public class Portfolio {
    private final Vector<Asset> assets;
    Portfolio() {
        assets = new Vector<>();
    }
    public final double valoreTot() {
        double ris = 0;
        for(Asset it: assets) {
            ris += it.getInvestimento();
        }
        return ris;
    }
    public final double gainTot() {
        double ris = 0;
        for(Asset it: assets)
            ris += it.totalGain();
        return ris;
    }
    public final void addAsset(Asset a){
        assets.add(a);
    }
    public final void removeAsset(int n) {
        assets.remove(n);
    }
    public final int getSize() {
        return assets.size();
    }
    public final Asset getAsset_n(int n) {
        return assets.get(n);
    }
    public void setTax(boolean b) {
        Asset.setTaxOn(b);
    }
    public int addUnionAsset(int n, int k) {
        boolean comp = true;
        Asset a = assets.elementAt(n);
        Asset b = assets.elementAt(k);
        if((a instanceof Stock) && (b instanceof Stock))
            assets.add((a.unionAsset(b)));
        else {
            if((a instanceof Bond) && (b instanceof Bond)) {
                Bond ba = (Bond)a;
                Bond bb = (Bond)b;
                if(ba.getStato() == bb.getStato())
                    assets.add(a.unionAsset(b));
                else
                    comp = false;
            }
            else {
                if((a instanceof Derivative) && (b instanceof Derivative)) {
                    Derivative da = (Derivative)a;
                    Derivative db = (Derivative)b;
                    if((da.getShort() == db.getShort()) && (da.getLeva() == db.getLeva()))
                        assets.add(a.unionAsset(b));
                    else comp = false;
                }
            }
        }
        if(comp) {
            assets.remove(a);
            assets.remove(b);
            return assets.size()-1;
        }
        return assets.size()+1;
    }
    public final double totalReturn() {
        return (this.valoreTot()+this.gainTot());
    }
}