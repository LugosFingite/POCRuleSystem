## La référence/doc/specs du Projet !!

### I) La structure du code :

*Le proto-projet en C++ est structuré ainsi :*

- La classe "Prompt" :
	-- Gère les interactions avec l'utilisateur et la gestion de l'IA
	-- Constructeur --> Initialise les rules et le moteur de script
-- run() --> sert à éxecuteur l'IA, contient une boucle qui récupère l'entrée via read(), et s'occupe de la faire matcher à la bonne règle pour l'exécuter
-- loadRules() --> charge les règles depuis le dossier 'rules()'
-- loadRuleNtoUnderstood() --> charge la règle à utiliser si l'entrée n'est pas comprise
-- loadRuleExit() --> charge la règle qui s'occupe de sortir du programme
-- read() --> rècupère l'entrée et la retourne

- le fichier 'database.hpp' et 'database.cpp' : 
-- exists(string) -> vérifie si une clé d'entrée existe dans la db
-- load(string, string) et load(string) -> récupère une valeur de la db, avec une version qui prend en compte une valeur par défaut
-- save(string, string) -> sauve une valeur dans la db
-- registerToScript(chai) -> détail d'implémentation, ajoute les fonctions de db au moteur de script

- le fichier 'parsing.hpp' et 'parsing.cpp'
-- parse_error et tout -> détail d'implémentation, exceptions
-- detail::replaceVariables(string, map) -> remplace les variables dans la règle en '`$nom`' avec les valeurs possédées
-- detail::buildTree() -> détail d'implémentation, construit l'arbre de l'entrée pour gèrer les règles imbriquées (comme '`((yo|plz) | héhé)`')
-- detail::collapseTree(Tree) -> detail d'implémentation, 'effondre' progressivement l'arbre en gèrant les règles imbriquées unes à unes des plus imbriquées vers le haut
-- parsePattern(string, map) -> s'occupe d'interpréter l'entrée de la règle en un string final choisi au hasard selon la structure de la règle (cf. partie règle)

- Structure Rule
-- Contient la règle et les logiques associées
-- matches(string) -> vérifie si une entrée correspond à la règle
-- answer(string, chai) -> répond à la règle selon une entrée donnée, via regex et compagnie
-- rulesFromJson(json) -> crée un objet Rule selon un fichier json

- UglyTree -> détail d'implémentation, implémentation personelle et degeulasse d'un arbre -> faites en un vous même en python, vous calquez pas sur le mien ! Voire faite autrement pour la partie parsing
 
- util.hpp -> détail d'implémentation
-- contient des fonctions utiles pour le POC, par forcément pertinentes pour le python, à voir

### 2) La structure des règles

Sous forme d'un fichier [JSON](https://fr.wikipedia.org/wiki/JavaScript_Object_Notation) :

exemple : 
```json

{
	"rules" : [
	{
		"input" : "(Mon nom est|Je m'appelle|Je suis) $nom\\.?",
		"script" : "",
		"answer" : "Tu t'appelles $nom . Quel âge as-tu ?"
	}
]
}
```

- "rules" : tableau qui contient les structures de règle du fichier (il peut effectivement y en avoir plusieurs !)

- "input" : Contient l'entrée, au format d'une [regex](https://fr.wikipedia.org/wiki/Expression_rationnelle) : si la regex correspond à l'entrée qu'on donne, la règle est retenue. Contient aussi des variables sous la forme $truc qui seront reconnues, et pourront donc être utlisées dans la partie script ou la partie réponse.

- "script" (optionnel) : contient le script d'interprétation de l'entrée (dans le langage de script de votre choix, le plus pratique en python ! Voire du python lui même !)

- "answer" : schéma de réponse : un string basique, qui contient des schémas de forme `(x|y)` , où une des deux opérandes (ici x ou y) est choisie au hasard, afin d'avoir une réponse en partie aléatoire qui fera moins 'robot'. Contient aussi des variables au format `$nom`, qui seront remplacées par leur valeur réelle dans la réponse.
