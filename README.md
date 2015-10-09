RSAtyricon
===========

0. Organisation du code
------------------------

Plusieurs répertoires contiennent les fichiers du TP :

- bin/ contient l'exécutable généré par le Makefile
- obj/ contient les fichiers obj générés par la Compilation
- include/ contient les fichiers header .h
- src/ contient les fichiers source .c
- source/ contient les fichiers source de chiffrement (i.e. Clair.txt)
- out/ contient les 3 fichiers de sortie du programme (prive.rsa, public.rsa, cipheredFile.txt, decipheredFile.txt)

Compilation : Saisir juste la commande "make", et la compilation est automatique

1. Vérification de primalité
-----------------------------

La vérification de la primalité est faite dans le fichier miller.c. On y trouve 3 fonctions :
- millerRabinStep(), qui est l'étape de calcul de millerRabin (boucle interne et test de primalité pour un seul nombre aléatoire)
- millerRabin(), qui est une fonction contenant la boucle de calcul (20 itérations), et la génération des nombres aléatoires a utilisés pour le calcul de primalité dans la boucle interne
- primeKeyGeneration(), qui est la fonction générant un nombre premier de 1024 bits utilisé dans RSA.

2. Génération de clé
---------------------

La génération de clé se fait dans le fichier key.c. Elle utilise tout d'abord les fonctions de 1. pour générer 2 nombres premiers de 1024 caractères. Puis elle calcule des opérations sur p et q afin de déterminer les caractéristiques (clés privées et publiques) pour cette instance du programme RSA. Ces clés sont stockées respectivement dans out/prive.rsa et out/public.rsa en hexadécimal

3. Chiffrement
---------------

La fonction de chiffrement est faite dans le fichier rsa_core.c. Elle récupère tout d'abord la clé publique dans le fichier afin de pouvoir chiffrer le message. Comme on ne peux pas faire des opérations de puissance modulaire sur l'ensemble du message, celui ci est découpé en petits morceaux afin d'être stocké dans le fichier out/cipheredFile.txt.

4. DéChiffrement
-----------------

De même, la fonction de déchiffrement récupère le texte chiffré dans le fichier précédemment et compute l'opération inverse à l'aide de la clé privée. On lit le texte découpé en différentes lignes dans le fichier chiffré et on réassemble le tout dans le fichier out/decipheredFile.txt

5. Padding
-----------

J'ai tenté de travailler sur le padding OAEP, mais j'ai eu de nombres difficultés à l'implémenter. J'ai eu beaucoup de mal à relier la théorie à la pratique, et notamment à la bibliothèque OpenSSL. J'ai supprimé les fichiers dans lesquels je n'ai pas réussi à faire d'implémentation correcte.

Conclusion
-----------

Le programme proposé permet une génération de clé à l'aide de 2 nombres dont la primalité a été testée avec un algorithme probabiliste de Miller Rabin. Le message stocké dans un fichier est chiffré puis déchiffré par les fonctions implementés dans le cadre de ce tp, ainsi que les 2 clés générées.
