# SAE-S1.01 

## Pour compiller

## Pour compiller et executer le prog
gcc -Wall -o debug\s1-01.exe main.c; if ($?) { .\debug\s1-01.exe }

## Lancer les commandes automatiquement à exécuter depuis le répertoire debug
cmd /c "s1-01.exe < in-xxx.txt"


## Compille est execute automatiquement
gcc -Wall -o debug\s1-01.exe main.c; if ($?) { cmd /c "debug\s1-01.exe < debug\in-sp1-1.txt" }


gcc -Wall -o debug\s1-01.exe main.c; if ($?) { cmd /c "debug\s1-01.exe < debug\in-sp1-1.txt > debug\res-sp1-1" }

gcc -Wall -o debug\s1-01.exe main.c; if ($?) { cmd /c "debug\s1-01.exe < debug\in-sp1-1.txt > debug\res-sp1-1" }




fc /w res-xxx.txt out-xxx.txt

Cette commande affiche "FC : aucune différence trouvée" si les 2 fichiers ne diffèrent que par des espaces et affiche les différences trouvées dans le cas contraire.

Si vous voulez aussi vérifier que les espaces sont bien respectés, il suffit de supprimer l'option /w. 

fc res-xxx.txt out-xxx.txt

La liste des commandes couvertes par chaque jeu de test est la suivante. 

* in-sp1.txt    : commandes "INSCRIRE", "PARTICIPANTS", "CREER" et "CONCOURS".
* in-sp2.txt    : commandes sp1 + "GAIN" et "SCORES"
* in-sp3.txt    : commandes sp2 + "CLASSEMENT" et "COMPARAISON"
* in-sp4.txt    : commande sp3 + "BILAN"

Pour toutes questions, vous pouvez m'écrire (denis.poitrenaud@u-paris.fr).