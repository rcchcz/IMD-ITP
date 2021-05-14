#cat campeonato.sh

#!/bin/bash
bot1=0
bot2=0
for (( i=0; i<100; i++ )); do 
    vencedor=$(node buraco.js bot1 bot2|grep venceu|sed -e 's/\(.*\.\)\(bot.*\)\(\ .*\)/\2/g');
    clear
    echo $vencedor ganhou!
    if [[ "${vencedor}" =~ "bot1" ]]; then ((bot1++)); fi
    if [[ "${vencedor}" =~ "bot2" ]]; then ((bot2++)); fi
    echo bot1 $bot1 X $bot2 bot2;
done