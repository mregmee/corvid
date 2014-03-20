var SVE_STRINGS = new Object();
SVE_STRINGS.DO_VERIFY = "Cliquer sur Vérifier l'expéditeur (SPF/DK) dans la barre de menu outils.";
SVE_STRINGS.SCANNING_HEADERS = "Scan de l'entête des messages en cours...";
SVE_STRINGS.SCANNING = "SVE: Scan en cours...";
SVE_STRINGS.NOT_APPLICABLE1 = "La vérification de l'expéditeur n'est pas aplicable pour ce message.";
SVE_STRINGS.NOT_APPLICABLE2 = "SVE: N'est pas Applicable";
SVE_STRINGS.CANNOT_FIND_FROM = "N'arrive pas a déterminer l'adresse de l'expéditeur à partir du courrier.";
SVE_STRINGS.MESSAGE_TOO_OLD = "Le Message est trop ancien pour en verifier l'expéditeur.";
SVE_STRINGS.MESSAGE_IN_FUTURE = "La date de ce Message est a venir. La vérification de son expéditeur saute.";
SVE_STRINGS.LOCAL_MAIL = "Le courier provient de votre serveur de courrier ou l'entête du message n'a su être interprétée.";
SVE_STRINGS.CHECKING_DK = "SVE: Vérification DK...";
SVE_STRINGS.DK_COMPUTING_SIGNATURE = "Calcul de la signature DomainKeys...";
SVE_STRINGS.DK_ABORTED1 = "La vérification DomainKeys prend trop de temps.  Pas de vérification de l'expéditeur possible.";
SVE_STRINGS.DK_ABORTED2 = "SVE: DK Annulée";
SVE_STRINGS.DK_CONTACTING_SERVER = "Appel du serveur de vérification DomainKeys...";
SVE_STRINGS.ERROR = "SVE: Erreur";
SVE_STRINGS.NO_EXPLANATION = "Pas d'explications disponibles pour ce message.";
SVE_STRINGS.MTACHECK = function(hostname) { return "L'expéditeur était " + hostname + ". Fait-il partie de votre réseau ?"; };
SVE_STRINGS.CONFIRMED = function(domain) { return "Le Domaine <" + domain + "> est Confirmé."; };
SVE_STRINGS.CONFIRMED2 = "SVE: Domaine Confirmé";
SVE_STRINGS.ENVELOPE_CONFIRMED = function(domain) { return "\"Du\" Domaine non vérifié. Enveloppe du domaine <" + domain + "> confirmée."; };
SVE_STRINGS.ENVELOPE_CONFIRMED2 = function(domain) { return "SVE: Domaine Réel: " + domain; };
SVE_STRINGS.FORWARDERCHECK = function(domain) { return "Est-ce que " + domain + " est une liste de courrier ?"; };
SVE_STRINGS.USER_NOT_CHECKED = function(user) { return "L'utilisateur \"" + user + "\" n'est pas vérifié."; };
SVE_STRINGS.DO_YOU_TRUST_DOMAIN = "Faites-vous confiance à ce domaine?";
SVE_STRINGS.ADDRESS_KNOWN = "Address is known to you."; // NEEDS TRANSLATING
SVE_STRINGS.DOMAIN_KNOWN = "Domain is known to you."; // NEEDS TRANSLATING
SVE_STRINGS.SENDER_UNKNOWN = "Sender is unknown to you."; // NEEDS TRANSLATING
SVE_STRINGS.VIA = function(via) { return "(via " + via + ")"; };
SVE_STRINGS.FORGED = function(domain) { return "Le domaine <" + domain + "> ne semble pas être la source légitime de ce courrier."; };
SVE_STRINGS.FORGED2 = "SVE: La Vérification a échouée";
SVE_STRINGS.NOT_SUPPORTED = "Le domaine expéditeur ne soutient pas la vérification (cette adresse peut être forgée).";
SVE_STRINGS.NOT_VERIFIED = "SVE: Non Vérifiée";
SVE_STRINGS.NEUTRAL = "Le domaine de l'expéditeur ne peut pas être vérifié (cette adresse peut être forgée).";
SVE_STRINGS.DK_NOT_CHECKED = "DomainKeys n'est pas vérifié; Cette adresse peut être forgée. (Activez DomainKeys dans Outils->Extention->Options)";
SVE_STRINGS.ATTACK = "Cet expéditeur est connu pour être un Spammeur ou un hameçonneur nuisible.  Eliminez cet E-mail!.";
SVE_STRINGS.ATTACK2 = "SVE: Attaque de Pouriel/hameçonnage";
SVE_STRINGS.ERROR2 = "Erreur:";
SVE_STRINGS.MAIL_LIST = function(domain) { return "Le Message venant du domaine <" + domain + "> est confirmé."; };
SVE_STRINGS.MAIL_LIST_EXPLANATION = "L'expéditeur original de cette liste de courrier ne peut vérifié.";
SVE_STRINGS.MAIL_LIST2 = function(domain) { return "SVE: Liste de courrier Confirmé de: " + domain; };
SVE_STRINGS.MAIL_LIST_UNVERIFIED = "Le domaine de la liste de courrier ne peut être vérifié ou ne gère pas la vérification.";
SVE_STRINGS.UNVERIFIED_POPUP_ALERT = "Le domaine expéditeur de ce courrier ne peut pas être vérifié.  Il est conseillé de ne pas donner suite à ce courrier, ni d'en récupérer les fichiers joints, ou de suivre les liens éventuels inscrits dans ce courrier.\n\nCet avertissement peut être désactivé dans l'option  Expéditeur Vérification Extention, qui se trouve dans Outils -> Extentions.";
SVE_STRINGS.CHECKING_RBLS1 = "Vérification de l'expéditeur dans les listes de SURBL/Spamhaus et hameçonnage...";
SVE_STRINGS.CHECKING_RBLS2 = "SVE: Vérification RBLs...";
SVE_STRINGS.BLACKLISTED = function(rbl) { return "L'éxpéditeur est listé dans " + rbl + " liste des Pouriels malicieux ou d'arnaque par hameçonnage."; };
SVE_STRINGS.SPF1 = "Vérification SPF en cours...";
SVE_STRINGS.SPF2 = "SVE: Vérification SPF...";
SVE_STRINGS.DNS_TAKING_TIME = "[Essayez de paramétrer le serveur DNS dans les options.]";
SVE_STRINGS.SERVER_ERROR = "Il y a eu une erreur du serveur.";
SVE_STRINGS.REPUTABLE_SENDER = "Expéditeur Honorable";
SVE_STRINGS.CHECK_DOMAIN_CAREFULLY = "Vérifier le domaine soigneusement.";
