# RSAtyricon

*Implementation of RSA in C*

## Code structure

The files are in the following folders of the git repository:

- bin/ where the executable file is generated
- obj/ where there is the object files
- include/ gathers the header files (.h)
- src/ gathers the source files (.c)
- source/ where there is the clear files to encrypt and decrypt
- out/ gathers the 3 output files of the program (prive.rsa, public.rsa, cipheredFile.txt, decipheredFile.txt)

Compilation: `make`

## Vérification de primalité


La vérification de la primalité est faite dans le fichier miller.c. On y trouve 3 fonctions :
- millerRabinStep(), qui est l'étape de calcul de millerRabin (boucle interne et test de primalité pour un seul nombre aléatoire)
- millerRabin(), qui est une fonction contenant la boucle de calcul (20 itérations), et la génération des nombres aléatoires a utilisés pour le calcul de primalité dans la boucle interne
- primeKeyGeneration(), qui est la fonction générant un nombre premier de 1024 bits utilisé dans RSA.

## Génération de clé

La génération de clé se fait dans le fichier key.c. Elle utilise tout d'abord les fonctions de 1. pour générer 2 nombres premiers de 1024 caractères. Puis elle calcule des opérations sur p et q afin de déterminer les caractéristiques (clés privées et publiques) pour cette instance du programme RSA. Ces clés sont stockées respectivement dans out/prive.rsa et out/public.rsa en hexadécimal

## Chiffrement

La fonction de chiffrement est faite dans le fichier rsa_core.c. Elle récupère tout d'abord la clé publique dans le fichier afin de pouvoir chiffrer le message. Comme on ne peux pas faire des opérations de puissance modulaire sur l'ensemble du message, celui ci est découpé en petits morceaux afin d'être stocké dans le fichier out/cipheredFile.txt.

## DéChiffrement

De même, la fonction de déchiffrement récupère le texte chiffré dans le fichier précédemment et compute l'opération inverse à l'aide de la clé privée. On lit le texte découpé en différentes lignes dans le fichier chiffré et on réassemble le tout dans le fichier out/decipheredFile.txt

## Padding

Le padding OAEP reste à implémenter (avec OpenSSL)

## Conclusion

Le programme proposé permet une génération de clé à l'aide de 2 nombres dont la primalité a été testée avec un algorithme probabiliste de Miller Rabin. Le message stocké dans un fichier est chiffré puis déchiffré par les fonctions implementés dans le cadre de ce tp, ainsi que les 2 clés générées.
