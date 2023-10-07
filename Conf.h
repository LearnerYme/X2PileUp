#ifndef __CENT_UTIL_CONFXXX__
#define __CENT_UTIL_CONFXXX__

// These parameters are using BES-II 17.3 GeV as template.
// Need to change with your own.

namespace cent_conf {
    
    static const char* Name = "17p3"; // with this name, will be easy to find if we are using a correct parameter list
    static const char* Mode = // uncomment current status, will help to know if we are using a correct parameter list as well
        // "TEST";
        "PU";
        // "LUMI";
        // "VZ";
        // "COMP";

    static const int nTrg = 1;
    static int trgList[nTrg] = {
        870010
    };

    // pile up arguments
    static double nTofMatch_upper_pars[4] = {
        /*
            3th order polynomial parameters.
        */
        9.71969, 0.532913, -0.00069537, 7.97491e-07
    };
    static double nTofMatch_lower_pars[4] = {
        /*
            3th order polynomial parameters.
        */
        -57.9111, 0.742572, -0.00156223, 1.42066e-06
    };
    static double beta_eta1_upper_pars[4] = {
        /*
            3th order polynomial parameters.
        */
        11.328, 0.790262, -0.000576608, 5.67717e-07
    };
    static double beta_eta1_lower_pars[4] = {
        /*
            3th order polynomial parameters.
        */
        -65.424, 1.01763, -0.00186575, 1.74405e-06
    };

    // luminosity arguments
    static double lumi_par[nTrg][2] = { // please follow the order of trigger id
        {0, 0},
    };

    // vz arguments
    static double vz_par[nTrg][7] = { // please follow the order of trigger id
        {591.52	,0.0021783	,-0.00115482	,5.69411e-06	,-2.26069e-07	,-1.09632e-09	,2.42791e-11},
    };
      
    // centrality split with RefMult3
    static int cent_edge[9] = { // here fill in the centrality bin edge 
        492, 413, 288, 196, 128, 79, 46, 24, 12
    };

} // namespace cent_conf


#endif
