function quickquote_doOk() {
  try {
    var b = document.getElementById("bundle_quickquote");
    quickquote_savePreferences(b);
  } catch (e) {
    alert(b.getString("quickquote.prefSaveError")+'\n' + e);
  }
  return true;
}

function quickquote_doCancel() {
  return true;
}

function quickquote_analize_gui(event) {
  try{
  var rewr = document.getElementById("rewr");
  var wc = document.getElementById('WC');
  var qs = document.getElementById('QS');
  var qslbl = document.getElementById('QSLBL');
  var qs2 = document.getElementById('QS2');
  var qs2lbl = document.getElementById('QS2LBL');
  var offsetlbl = document.getElementById('OFFSETLBL');
  var offsettxt = document.getElementById('OFFSETTXT');
  var delaytxt = document.getElementById('DELAYTXT');
  
  if (event.target == rewr) {
    wc.disabled = rewr.checked; 
  }
  else if (event.target == document.getElementById('nonclip') ||
           event.target == document.getElementById('clip')) {
    rewr.disabled = false;
    wc.disabled = !rewr.checked;
    qs.disabled = false;
    qslbl.disabled = false;
    qs2.disabled = false;
    qs2lbl.disabled = false;
    offsettxt.disabled = false;
    offsetlbl.disabled = false;
    delaytxt.value="1000";
  }
  else {
    rewr.checked = false;
    rewr.disabled = true;
    wc.disabled = true;
    qs.disabled = true;
    qslbl.disabled = true;    
    qs2.disabled = true;
    qs2lbl.disabled = true;  
    offsettxt.disabled = true;
    offsetlbl.disabled = true;      
    delaytxt.value="500";
  }
  if (!wc.disabled && wc.value=="") {
    wc.value = "72";
  }
  if (!offsetlbl.disabled && offsettxt.value=="") {
    offsettxt.value = "4";
  }
  }catch(ex){alert(ex.message);}
}

function quickquote_loadPreferences() {
  try{
  var prefs = new quickquotePrefs();
  prefs.load();
  var rewr = document.getElementById("rewr");
  var wc = document.getElementById('WC');
  var qs = document.getElementById('QS');
  var qslbl = document.getElementById('QSLBL');  
  var qs2 = document.getElementById('QS2');
  var qs2lbl = document.getElementById('QS2LBL');  
  document.getElementById('QS').value=prefs.qs;
  document.getElementById('QS2').value=prefs.qs2;
  document.getElementById('RTS').value=prefs.rts;
  document.getElementById('BQ').value=prefs.bq;
  document.getElementById('AQ').value=prefs.aq;
  document.getElementById('workway').selectedIndex=prefs.work;
  document.getElementById('subnew').checked = prefs.subnew;
  document.getElementById('OFFSETTXT').value = prefs.offset;
  document.getElementById('OFFSETTXT').disabled = prefs.work==PASTE;
  document.getElementById('OFFSETLBL').disabled = prefs.work==PASTE;
  document.getElementById('DELAYTXT').value = prefs.delay;
  document.getElementById('REPLREPLY').checked = prefs.quotereply;
  document.getElementById('REPLREPLYALL').checked = prefs.quotereplyall;  
  if (prefs.wc>0) {
    rewr.checked = true;
    wc.value = ""+prefs.wc;
  }
  else {
    wc.disabled = true;
    if (prefs.work==2) {
      rewr.disabled = true;
      qs.disabled = true;
      qslbl.disabled = true;        
      qs2.disabled = true;
      qs2lbl.disabled = true;
    }
  }
  }catch(ex){alert(ex.message);}
}

function quickquote_savePreferences(b) {
  var prefs = new quickquotePrefs();
  prefs.qs = document.getElementById('QS').value;
  prefs.qs2 = document.getElementById('QS2').value;
  prefs.rts = document.getElementById('RTS').value;
  prefs.bq = document.getElementById('BQ').value;
  prefs.aq = document.getElementById('AQ').value;
  prefs.work = document.getElementById('workway').selectedIndex;
  prefs.subnew = document.getElementById('subnew').checked;
  prefs.quotereply = document.getElementById('REPLREPLY').checked;
  prefs.quotereplyall = document.getElementById('REPLREPLYALL').checked;
  if (document.getElementById('rewr').checked) {
    prefs.wc = +(document.getElementById('WC').value);
    if (prefs.wc<=0 || prefs.wc.toString()=="NaN") {
      alert(document.getElementById('WC').value+" "+b.getString("quickquote.fieldNotValid"));
      prefs.wc = 72;
    }
  }
  else 
    prefs.wc = -1;
  prefs.delay = +(document.getElementById('DELAYTXT').value);
  if (prefs.delay<0 || prefs.delay.toString()=="NaN") {
    alert(document.getElementById('DELAYTXT').value+" "+b.getString("quickquote.fieldNotValid"));
    prefs.delay = prefs.work==PASTE?500:1000;
  }
  if (prefs.work!=PASTE) {
    prefs.offset = +(document.getElementById('OFFSETTXT').value);
    if (prefs.offset<0 || prefs.offset.toString()=="NaN") {
      alert(document.getElementById('OFFSETTXT').value+" "+b.getString("quickquote.fieldNotValid"));
      prefs.offset = 4;
    }    
  }
  prefs.save();
}