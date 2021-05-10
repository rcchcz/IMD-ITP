// This program prints the final results of a football season.

#include <stdio.h>

int main()
{
    int n;

    scanf("%d", &n);

    int ps, pb, TTDs, TFGs, TPATs, TTDb, TFGb, TPATb;
    ps = pb = TTDs = TFGs = TPATs = TTDb = TFGb = TPATb = 0;

    for(int i = 0; i < n; i++)
    {
        int TDs, FGs, PATs, TDb, FGb, PATb;
        scanf("%d %d %d", &TDs, &FGs, &PATs);
        scanf("%d %d %d", &TDb, &FGb, &PATb);
        ps += (6*TDs) + (3*FGs) + PATs;
        pb += (6*TDb) + (3*FGb) + PATb;
        TTDs += TDs;
        TFGs += FGs;
        TPATs += PATs;
        TTDb += TDb;
        TFGb += FGb;
        TPATb += PATb;
    }

    if(ps > pb) printf("Saints é o campeão na série histórica!\nPlacar: %d x %d\n", ps, pb);
    if(ps < pb) printf("Bucaneers é o campeão na série histórica!\nPlacar: %d x %d\n", pb, ps);
    if(ps == pb) printf("Série histórica empatada em %d pontos!\n", ps);

    if(TTDs > TTDb) printf("Saints marcou mais Touch Downs(%d)\n", TTDs);
    if(TTDs < TTDb) printf("Bucaneers marcou mais Touch Downs(%d)\n", TTDb);
    if(TTDs == TTDb) printf("Número de Touch Downs empatado(%d)\n", TTDs);

    if(TFGs > TFGb) printf("Saints marcou mais Field Goals(%d)\n", TFGs);
    if(TFGs < TFGb) printf("Bucaneers marcou mais Field Goals(%d)\n", TFGb);
    if(TFGs == TFGb) printf("Número de Field Goals empatado(%d)\n", TFGb);

    if(TPATs > TPATb) printf("Saints marcou mais Pontos Extras(%d)\n", TPATs);
    if(TPATs < TPATb) printf("Saints marcou mais Pontos Extras(%d)\n", TPATb);
    if(TPATs == TPATb) printf("Número de Pontos Extras empatado(%d)\n", TPATs);

    return 0;
}