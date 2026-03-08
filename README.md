# Traduction Française - TabletopTweaks Base
Ce projet propose une localisation française complète et rigoureuse pour le mod TabletopTweaks Base (Pathfinder: Wrath of the Righteous).

## Installation
1- Prérequis : Installez le mod original TabletopTweaks-Base.

2- Téléchargez le fichier LocalizationPack.json présent dans ce dépôt.

3- Rendez-vous dans le dossier d'installation du mod.

Via Modfinder : Faites un clic droit sur le mod -> Open Folder, puis ouvrez le sous-dossier Localization.
  
Manuellement : ...\Pathfinder Wrath of the Righteous\Mods\TabletopTweaks-Base\Localization\

4- Renommez LocalizationPack.json en LocalizationPack.json.bak

5- Placez le fichier LocalizationPack.json de cette traduction dans le même dossier.

6- Lancez le jeu.

## Désinstallation
1- Rendez-vous dans le dossier d'installation du mod. (cf : Installation)

2- Supprimez le fichier LocalizationPack.json

3- Renommez LocalizationPack.json.bak en LocalizationPack.json

4- C'est fait !

## Philosophie de traduction
La traduction a été réalisée via un processus hybride (automatisation + révision manuelle) avec une hiérarchie de priorité stricte pour garantir l'immersion :

Fidélité à la version d'Owlcat Games : Cohérence avec les termes déjà présents dans le jeu vidéo.

Fidélité à Pathfinder 1ère Édition : Utilisation du lexique officiel de Black Book Editions pour tous les dons, archétypes, ...

# Contributions
Le projet est ouvert aux améliorations. Si vous repérez une coquille, un terme non traduit ou une erreur de lexique :

Pull Requests : Les propositions de corrections sont les bienvenues !

Signalement : Vous pouvez également ouvrir une Issue pour signaler un problème spécifique.

## État du projet
[x] Traduction initiale terminée.

[x] Révision des termes techniques (Dons, Sorts, Aptitudes).

[ ] Intégration officielle (Soumission envoyée à l'auteur original du mod pour une inclusion native).

## Crédits
Auteur du mod original : Vek17

Traduction : Tyraen1er

Contributeur : LittleLazyGhost (alias JuanFaDu)

Sources : Owlcat Games, Black Book Editions (Pathfinder JdR).

## Développement
Le projet utilise des outils personnalisés en C++ pour automatiser la synchronisation et garantir l'intégrité des fichiers lors des mises à jour du mod original.

Le processus suit une chaîne de traitement en trois étapes :

### Extraction de l'anglais (createReplace-enGB.cpp)

Entrée : LocalizationPack.json (original du mod).

Sortie : anglais_seulement.json.

Rôle : Isole toutes les lignes "enGB": pour offrir une base de travail propre, sans risque de modifier la structure JSON du mod.

### Phase de Traduction

L'utilisateur doit convertir le contenu de anglais_seulement.json vers un nouveau fichier nommé francais_seulement.json.

Note critique : L'ordre des lignes et le nombre total d'entrées doivent être rigoureusement conservés pour permettre l'injection correcte.

Injection du français (replaceFR.cpp) :

Entrées : francais_seulement.json + LocalizationPack.json (original).

Sortie : LocalizationPack.json (version finale traduite).

Sécurité : Le programme compare le nombre d'entrées et s'arrête en cas de désynchronisation, indiquant la ligne exacte de l'erreur.

### Compilation des outils

Si vous souhaitez compiler les outils de développement :

g++ -std=c++17 createReplace-enGB.cpp -o createReplace-enGB

g++ -std=c++17 replaceFR.cpp -o replaceFR
