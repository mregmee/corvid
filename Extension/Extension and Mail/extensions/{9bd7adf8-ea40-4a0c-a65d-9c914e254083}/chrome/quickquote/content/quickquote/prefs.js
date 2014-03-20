const GET_SEL = 0;
const CLIP = 1;
const PASTE = 2;
const NEWMSG = 0;
const REPLY = 1;
const NEWS = 2;
const REPLYALL = 3;
const CURRMSG = 4;

function quickquotePrefs () {
  var prefService = Components.classes["@mozilla.org/preferences-service;1"]
      .getService(Components.interfaces.nsIPrefService).getBranch(
      "extensions.quickquote.");
  this.prefService = prefService;
  
  this.operation = REPLY;
  this.wc = 72;
  this.work = CLIP;
  this.lng="0";
  this.id="";
  this.subj="";
  this.news="";
  this.to="";
  this.aemail = "";
  this.aname="";
  this.date = "";
  this.time = "";
  this.delay = 500;
  this.offset = 4;
  this.quotereply=false;
  

  this.loadTmp = function() {
    var str = "";
    if (prefService.prefHasUserValue("quickquote_phrase")) {
      str = prefService.getCharPref("quickquote_phrase");
    }
    this.phrase = str;

    str = "";
    if (prefService.prefHasUserValue("quickquote_to")) {
      str = prefService.getCharPref("quickquote_to");
    }
    this.to = str;
  
    str = "";
    if (prefService.prefHasUserValue("quickquote_subj")) {
      str = prefService.getCharPref("quickquote_subj");
    }
    this.subj = str;
    
    str = "0";
    if (prefService.prefHasUserValue("quickquote_lng")) {
      str = prefService.getCharPref("quickquote_lng");
    }
    this.lng = str;

    str = "";
    if (prefService.prefHasUserValue("quickquote_news")) {
      str = prefService.getCharPref("quickquote_news");
    }
    this.news = str;

    str = "";
    if (prefService.prefHasUserValue("quickquote_id")) {
      str = prefService.getCharPref("quickquote_id");
    }
    this.id = str;    
    
    str = 0;
    if (prefService.prefHasUserValue("quickquote_operation")) {
      str = prefService.getIntPref("quickquote_operation");
    }
    this.operation = str;    
  }
  
  this.load = function() {
    var str = "> ";
    if (prefService.prefHasUserValue("quickquote_qs")) {
      str = prefService.getCharPref("quickquote_qs");
    }
    this.qs = str;

    str = "";
    if (prefService.prefHasUserValue("quickquote_qs2")) {
      str = prefService.getCharPref("quickquote_qs2");
    }
    this.qs2 = str;
    
    str = "Re: ";
    if (prefService.prefHasUserValue("quickquote_rts")) {
      str = prefService.getCharPref("quickquote_rts");
    }
    this.rts = str;    
    
    str = "On %date %author wrote:";
    if (prefService.prefHasUserValue("quickquote_bq")) {
      str = prefService.getCharPref("quickquote_bq");
    }
    this.bq = str;    
    
    str = "";
    if (prefService.prefHasUserValue("quickquote_aq")) {
      str = prefService.getCharPref("quickquote_aq");
    }
    this.aq = str;
    
    str = CLIP;
    if (prefService.prefHasUserValue("quickquote_workway")) {
      str = prefService.getIntPref("quickquote_workway");
    }
    this.work = str;
    
    str = 72;
    if (prefService.prefHasUserValue("quickquote_wc")) {
      str = prefService.getIntPref("quickquote_wc");
    }
    this.wc = str;
    
    str = this.work==PASTE?500:1000;
    if (prefService.prefHasUserValue("quickquote_delay")) {
      str = prefService.getIntPref("quickquote_delay");
    }
    this.delay = str;    

    str = 4;
    if (prefService.prefHasUserValue("quickquote_offset")) {
      str = prefService.getIntPref("quickquote_offset");
    }
    this.offset = str;
    
    str = false;
    if (prefService.prefHasUserValue("quickquote_subnew")) {
      str = prefService.getBoolPref("quickquote_subnew");
    }
    this.subnew = str;
    
    str = false;
    if (prefService.prefHasUserValue("quickquote_quotereply")) {
      str = prefService.getBoolPref("quickquote_quotereply");
    }
    this.quotereply = str;    
    
    str = false;
    if (prefService.prefHasUserValue("quickquote_quotereplyall")) {
      str = prefService.getBoolPref("quickquote_quotereplyall");
    }
    this.quotereplyall = str;        
  }
  
  this.resetTmp = function() {
    this.phrase="";
    prefService.setCharPref("quickquote_phrase", "");
    this.to="";
    prefService.setCharPref("quickquote_to", "");
    this.subj="";
    prefService.setCharPref("quickquote_subj", "");
    this.news="";
    prefService.setCharPref("quickquote_news", "");   
    this.id="";
    prefService.setCharPref("quickquote_id", "");   
    prefService.setCharPref("quickquote_lng", "0");   
    this.aemail = "";
    this.aname="";    
    this.date = "";
    this.time = "";
  }
  this.saveTmp = function() {
    prefService.setCharPref("quickquote_phrase", this.phrase);
    prefService.setCharPref("quickquote_to", this.to);
    prefService.setCharPref("quickquote_subj", this.subj);
    prefService.setCharPref("quickquote_news", this.news);
    prefService.setCharPref("quickquote_id", this.id);
    prefService.setIntPref("quickquote_operation", this.operation);
    prefService.setCharPref("quickquote_lng", this.lng);    
  }
  this.save = function() {
    prefService.setCharPref("quickquote_qs", this.qs);
    prefService.setCharPref("quickquote_qs2", this.qs2);
    prefService.setCharPref("quickquote_rts", this.rts);
    prefService.setCharPref("quickquote_bq", this.bq);
    prefService.setCharPref("quickquote_aq", this.aq);
    prefService.setIntPref("quickquote_workway", this.work);
    prefService.setIntPref("quickquote_wc", this.wc);
    prefService.setIntPref("quickquote_delay", this.delay);
    prefService.setIntPref("quickquote_offset", this.offset);
    prefService.setBoolPref("quickquote_subnew", this.subnew);
    prefService.setBoolPref("quickquote_quotereply", this.quotereply);
    prefService.setBoolPref("quickquote_quotereplyall", this.quotereplyall);
  }
}
