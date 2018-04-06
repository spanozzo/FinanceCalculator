public class Use {
    public static void main(String args[]) {
        Stock s1 = new Stock("S1", 10.55, 11.71, 500, 0.15);
        Stock s2 = new Stock("S2", 5.88, 4.46, 100, 0.18);
        Bond b1 = new Bond("B1", 100, 100, 100, 1.8, true);
        Bond b2 = new Bond("B2", 100, 101, 100, 3.5, false);
        Derivative d1 = new Derivative("D1", 1.98, 2.02, 100, 100, false);
        Derivative d2 = new Derivative("D2", 26.5, 26.03, 100, 10, true);
        Portfolio p = new Portfolio();
        p.addAsset(s1); p.addAsset(s2);
        p.addAsset(b1); p.addAsset(b2);
        p.addAsset(d1); p.addAsset(d2);
        //Esempi sui singoli dati
        System.out.print("Investimento S1:" + s1.getInvestimento() + "; S1 gain:" + s1.gain(500) + "; S1 gain dividendo:" + s1.gainDividendo() 
                            + "; S1 gain totale:" + s1.totalGain() + "; S1 ROI%:" + s1.roi() + "\n");
        System.out.print("Investimento S2:" + s2.getInvestimento() + "; S2 gain:" + s2.gain(100) + "; S2 gain dividendo:" + s2.gainDividendo() 
                            + "; S2 gain totale:" + s2.totalGain() + "; S2 ROI%:" + s2.roi() + "\n");
        System.out.print("Investimento B1:" + b1.getInvestimento() + "; B1 gain:" + b1.gain(100) + "; B1 gain cedola:" + b1.gainCedola()
                            + "; B1 gain totale:" + b1.totalGain() + "; B1 ROI%:" + b1.roi() + "\n");
        System.out.print("Investimento B2:" + b2.getInvestimento() + "; B2 gain:" + b2.gain(100) + "; B2 gain cedola:" + b2.gainCedola()
                            + "; B2 gain totale:" + b2.totalGain() + "; B2 ROI%:" + b2.roi() + "\n");
        System.out.print("Investimento D1:" + d1.getInvestimento() + "; D1 gain totale:" + d1.totalGain() + "; D1 ROI%:" + d1.roi() + "\n");
        System.out.print("Investimento D2:" + d2.getInvestimento() + "; D2 gain totale:" + d2.totalGain() + "; D2 ROI%:" + d2.roi() + "\n");
        //Esempi sui singoli dati con tassazione attivata
        p.setTax(true); System.out.print("Tassazione On\n");
        System.out.print("Investimento S1:" + s1.getInvestimento() + "; S1 gain:" + s1.gain(500) + "; S1 gain dividendo:" + s1.gainDividendo() 
                            + "; S1 gain totale:" + s1.totalGain() + "; S1 ROI%:" + s1.roi() + "\n");
        System.out.print("Investimento S2:" + s2.getInvestimento() + "; S2 gain:" + s2.gain(100) + "; S2 gain dividendo:" + s2.gainDividendo() 
                            + "; S2 gain totale:" + s2.totalGain() + "; S2 ROI%:" + s2.roi() + "\n");
        System.out.print("Investimento B1:" + b1.getInvestimento() + "; B1 gain:" + b1.gain(100) + "; B1 gain cedola:" + b1.gainCedola()
                            + "; B1 gain totale:" + b1.totalGain() + "; B1 ROI%:" + b1.roi() + "\n");
        System.out.print("Investimento B2:" + b2.getInvestimento() + "; B2 gain:" + b2.gain(100) + "; B2 gain cedola:" + b2.gainCedola()
                            + "; B2 gain totale:" + b2.totalGain() + "; B2 ROI%:" + b2.roi() + "\n");
        System.out.print("Investimento D1:" + d1.getInvestimento() + "; D1 gain totale:" + d1.totalGain() + "; D1 ROI%:" + d1.roi() + "\n");
        System.out.print("Investimento D2:" + d2.getInvestimento() + "; D2 gain totale:" + d2.totalGain() + "; D2 ROI%:" + d2.roi() + "\n");
        p.setTax(false); System.out.print("Tassazione Off\n");
        //Esempio addizione
        System.out.print("Gain totale S1 + D2:" + s1.add(d2) + "\n");
        //Esempio calcolo differenza % sui gain totali
        System.out.print("Differenza % gain S1 e D2:" + s1.diffgain(d2) + "\n");
        //Esempio unione S1 e S2 (asset in posizione 0 e 1)
        int k = p.addUnionAsset(0, 1);
        Stock s12 = (Stock)p.getAsset_n(k);
        System.out.print("S1 Unione S2:(" + "Investimento S12:" + s12.getInvestimento() + "; S12 gain:" + s12.gain(s12.getUnit()) + "; S12 gain dividendo:" + s12.gainDividendo() 
                            + "; S12 gain totale:" + s12.totalGain() + "; S12 ROI%:" + s12.roi() + ")\n");
        // Esempio valore totale del portfolio con guadagni
        System.out.print("Valore Totale:" + p.totalReturn() + "\n");
        // Esempio guadagno totale investimenti portfolio
        System.out.print("Gain Totale:" + p.gainTot() + "\n");
    }
}
