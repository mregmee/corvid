var init = false;
var prefs = null;

//function insertLineBreak(editor) {
//  if (gCurrentIdentity.composeHtml) {
//    editor.insertText("dddddddddd\n<br>");
//  }
//  else {
//    editor.insertText("\n");
//  }   
//}

var cursObserver = { 
  observe: function(aSubject, aTopic, aData) {
    var editor = GetCurrentEditor();
    try{
      var wholeDocRange = editor.document.createRange();
      var rootNode = editor.rootElement.QueryInterface(Components.interfaces.nsIDOMNode);
      wholeDocRange.selectNodeContents(rootNode);
      var range = editor.document.createRange();
      eot = wholeDocRange.endOffset;
      var sot = eot-prefs.offset;
      if (sot<wholeDocRange.startOffset) {
        sot = wholeDocRange.startOffset;
      }
      range.setStart(wholeDocRange.startContainer,sot);
      range.setEnd(wholeDocRange.endContainer,eot);
      editor.selection.addRange(range);
      var win = document.getElementById("content-frame").contentWindow;
      win.scrollTo(0,win.scrollMaxY);
    }
    catch(exs) {
      alert(exs);
    }    
  }
}

var sigObserver = { 
  observe: function(aSubject, aTopic, aData) {
    try{
      var editor = GetCurrentEditor();
      clipboardWithHtmlBody(editor);
      var win = document.getElementById("content-frame").contentWindow;
      win.scrollTo(0,win.scrollMaxY);    
    }
    catch(exs) {
      alert(exs);
    }
  }
}

var sigObserver2 = { 
  observe: function(aSubject, aTopic, aData) {
    try{
      var editor = GetCurrentEditor();
      addSignature(editor);
    }
    catch(exs) {
      alert(exs);
    }
  }
}

var timer;
var timer2;
var bq = "";
var aq = "";

function clipboardWithHtmlBody(editor) {
  try {
    editor.QueryInterface(Components.interfaces.nsIEditorMailSupport);
    editor.beginTransaction();
    if (bq!="")
      editor.insertText(bq);
    editor.pasteAsQuotation(1);
    if (aq!="")
      editor.insertText(aq);
    editor.endTransaction();
  }
  catch (exs) {
  }
}

function initEditor(editor) {
  editor.QueryInterface(Components.interfaces.nsIHTMLEditor);
  editor.QueryInterface(Components.interfaces.nsIPlaintextEditor);
  editor.QueryInterface(Components.interfaces.nsIEditorMailSupport);  
}

function editBodyPaste() {
  try {
  var editor = GetCurrentEditor();
  initEditor(editor);
  var editor = GetCurrentEditor();
  if (prefs.operation!=CURRMSG && gCurrentIdentity.sigBottom)
    addSignature(editor);
  editor.beginTransaction();
  if (gCurrentIdentity.replyOnTop==1)
    bq = "\n";
  if (prefs.bq!="")
    bq+= replaceAll(prefs.bq)+"\n";
  if (prefs.aq!="")
    aq = "\n"+replaceAll(prefs.aq);
  if (gCurrentIdentity.replyOnTop!=1)
    aq+="\n";          
  if (gCurrentIdentity.attachSignature && gCurrentIdentity.sigBottom) {             
    timer = Components.classes["@mozilla.org/timer;1"].createInstance(Components.interfaces.nsITimer);
    timer.init(sigObserver,prefs.delay,timer.TYPE_ONE_SHOT);        
  }
  else
    clipboardWithHtmlBody(editor);
  editor.endTransaction();
  if (prefs.operation!=CURRMSG && !gCurrentIdentity.sigBottom) {
    timer = Components.classes["@mozilla.org/timer;1"].createInstance(Components.interfaces.nsITimer);
    timer.init(sigObserver2,prefs.delay,timer.TYPE_ONE_SHOT);        
  }
}catch(ex) {alert(ex);}
}

function editBody() {
  var editor = GetCurrentEditor();
  initEditor(editor);
  if (prefs.operation!=CURRMSG && gCurrentIdentity.sigBottom)
    addSignature(editor);
  editor.beginTransaction();
  var rv = true;
  var timerselect = false;
  try {
    editor.insertTextWithQuotations(prefs.phrase);
    timerselect = gCurrentIdentity.replyOnTop!=1 && prefs.operation!=NEWMSG && prefs.operation!=CURRMSG;
    if (timerselect) {
      timer2 = Components.classes["@mozilla.org/timer;1"].createInstance(Components.interfaces.nsITimer);
      timer2.init(cursObserver,prefs.delay,timer2.TYPE_ONE_SHOT);
    }      
  }
  catch(ex) {
    rv = false;
  }
  editor.endTransaction();
  if (!timerselect && gCurrentIdentity.replyOnTop!=1 && prefs.operation!=CURRMSG) {
    var win = document.getElementById("content-frame").contentWindow;
    win.scrollTo(0,win.scrollMaxY);    
  }
  if (prefs.operation!=CURRMSG && !gCurrentIdentity.sigBottom)
    addSignature(editor);  
  return rv;
}

function addSignature(editor) {
  var orig = gCurrentIdentity.autoQuote
  gCurrentIdentity.autoQuote = false;
  var editorStyle = editor.QueryInterface(Components.interfaces.nsIEditorStyleSheets);
  editorStyle.addStyleSheet("chrome://messenger/skin/messageQuotes.css");
  //alert(gMsgCompose.compFields.messageId+"|"+gMsgCompose.compFields.subject+"| "+gMsgCompose.compFields.references+"|"+gMsgCompose.compFields.cc+"| "+gMsgCompose.compFields.to);
  gMsgCompose.initEditor(editor, window.content);
  gCurrentIdentity.autoQuote = orig;
}

function editSubj() {
  var subTB = document.getElementById('msgSubject');
  if (subTB!=null) {
    if (prefs.subj.indexOf("Re: ")==0 && prefs.operation!=NEWMSG) {
      prefs.subj = prefs.subj.substring(4);
    }
    if (prefs.subj.indexOf(prefs.rts)==0 || prefs.operation==NEWMSG) {
      gMsgCompose.compFields.subject = prefs.subj;
    }
    else
      gMsgCompose.compFields.subject = prefs.rts+prefs.subj;
    subTB.value = gMsgCompose.compFields.subject;
  }
}

//function editTo(prefs) {
//  if (prefs.operation==REPLY) {
//    var toTB = document.getElementById('addressCol2#1');
//    if (toTB!=null) {
//      toTB.value = prefs.replyto!=""?prefs.replyto:prefs.to;
//      document.getElementById('addressCol1#1').selectedIndex = 0;
//    }  
//  }
//  else if (prefs.operation==REPLYALL) {
//    if (prefs.news2!="")
//      parseAndAddAddresses2(prefs.news2,"addr_newsgroups",prefs.news);
//    AddRecipient("addr_to",prefs.replyto!=""?prefs.replyto:prefs.to);       
//    parseAndAddAddresses2(prefs.recipients,"addr_cc",gCurrentIdentity.email);
//    parseAndAddAddresses2(prefs.cc,"addr_cc",gCurrentIdentity.email);
//  }
//}

//function parseAndAddAddresses2(addressText, recipientType,toRemove)
//{
//  try{
//  // strip any leading >> characters inserted by the autocomplete widget
//  var strippedAddresses = addressText.replace(/.* >> /, "");
//  var hdrParser = Components.classes["@mozilla.org/messenger/headerparser;1"].getService(Components.interfaces.nsIMsgHeaderParser);
//  var addresses = {};
//  var names = {};
//  var fullNames = {};
//  var numAddresses = hdrParser.parseHeadersWithArray(strippedAddresses, addresses, names, fullNames);
//  if (numAddresses > 0)
//  {
//    var num = 0;
//    for (i=0; i<numAddresses; i++) {
//      fullNames.value[i-num] = fullNames.value[i];
//      if (addresses.value[i]==toRemove) {
//        num++;
//      }
//    }
//    numAddresses-=num;
//    fullNames.value[numAddresses] = null;
//    // we need to set up our own autocomplete session and search for results
//
//    setupAutocomplete(); // be safe, make sure we are setup
//    if (!gAutomatedAutoCompleteListener)
//      gAutomatedAutoCompleteListener = new AutomatedAutoCompleteHandler();
//
//    gAutomatedAutoCompleteListener.init(fullNames.value, numAddresses, recipientType);
//  }
//  }catch(ex){alert("UUUUUUUUUUU "+ex)};
//}

function quickquote_add(event) {
  try {
    if (event==null || ((event.type=="click" && event.button==1) || event.type=="keypress" || 
      event.target==document.getElementById("quickquote_curr"))) {
      if (event!=null) {
        prefs.loadTmp();
        if (prefs.operation!=CURRMSG)
          return;
      }
      var currentphrase = prefs.phrase;
      if (currentphrase!=null && currentphrase.length>0) {
        prefs.load();
        if (prefs.work!=PASTE)
          adjustPhrase();
        if (prefs.operation!=CURRMSG && (prefs.operation!=NEWMSG||prefs.subnew)) {
          if (prefs.rts!="Re: " || prefs.operation==NEWMSG) {
            editSubj();
          }
        }
        if (prefs.work!=PASTE)
          editBody();
        else
          editBodyPaste();
        prefs.resetTmp();
        //document.getElementById("content-frame").contentWindow.focus();
      }
    }
  }
  catch(ex){
    alert(ex);
  }
}

var msgEditorCreationObserver2 = { 
  observe: function(aSubject, aTopic, aData) {
    if (aTopic == "obs_documentCreated") {
      var editor = GetCurrentEditor();
      if (editor && GetCurrentCommandManager() == aSubject) {       
        quickquote_add(null);
      }
    }
  }
}

function quickquote_init2() {
  if (!init) {
    prefs = new quickquotePrefs();
    prefs.loadTmp();
    if (prefs.phrase!="") {
      var oContext = null;
      if (prefs.operation!=CURRMSG) {
        oContext = document.getElementById('msgcomposeWindow');
        if (oContext!=null) {
          oContext.setAttribute("onload", ""+ oContext.getAttribute("onload")+
          "; GetCurrentCommandManager().removeCommandObserver(gMsgEditorCreationObserver, 'obs_documentCreated');"+ 
          "GetCurrentCommandManager().addCommandObserver(msgEditorCreationObserver2, 'obs_documentCreated');");
        }
      }
      oContext = document.getElementById('content-frame');
      if (oContext!=null) {
        oContext.addEventListener("click",quickquote_add,false);
      }
    }
    init = true;
  }
}

/*function onl() {
  var msgCC = document.getElementById("msgComposeContext");
  if (msgCC!=null) {
    msgCC.addEventListener("popupshowing",quickquote_collapse_if_necessary2,false);
  }     
}

function quickquote_collapse_if_necessary2() {
  var prefs = new quickquotePrefs();
  prefs.loadTmp();
  try{
  document.getElementById("quickquote_sep").collapsed = prefs.operation!=CURRMSG || prefs.phrase=="";
  //document.getElementById("quickquote_curr").collapsed = prefs.operation!=CURRMSG || prefs.phrase=="";
  }catch(ex) {alert("HHHHHHHHHHHH "+ex.message);}
}*/

function preprocessPhrase(phrase) {
  phrase = phrase.replace(/\r\n/gi,"\n");
  phrase = phrase.replace(/<br {0,}\/{0,1}>/gi,"\n");
  return phrase.replace(/\t/gi,"    ");
}

function postprocessPhrase(phrase) {
  //phrase = phrase.replace(/\n/gi,"<br />");
  return phrase.replace(/\t/gi,"&nbsp;&nbsp;&nbsp;&nbsp;");  
}

function adjustPhrase() {
  try {
    prefs.phrase = preprocessPhrase(prefs.phrase);
    var qstate = new Array(2);
    if (gCurrentIdentity.replyOnTop!=1 || prefs.operation==CURRMSG) {
      qstate[0] = 0;
      qstate[1] = 1;
    }
    else {
      qstate[0] = 1;
      qstate[1] = 0;
    }
    if (prefs.operation!=CURRMSG) {
      prefs.bq = replaceAll(prefs.bq);
      prefs.aq = replaceAll(prefs.aq);
      var newphr=gCurrentIdentity.replyOnTop!=1?"":"\n";
      if (prefs.bq.length>0) {
        newphr+= prefs.bq+"\n";
        qstate[0]++;
      }
      newphr+=prefs.phrase;
      if (prefs.aq.length>0 || gCurrentIdentity.replyOnTop!=1) {
        newphr+="\n";
      }
      if (prefs.aq.length>0) {
        newphr +=prefs.aq;
        if (gCurrentIdentity.replyOnTop!=1) {
          newphr+="\n";
        }
        qstate[1]++;
      }
      prefs.phrase = newphr;
    }
    else  
      prefs.phrase+="\n";
    if (prefs.wc>0) {
      prefs.phrase = rewrap(qstate);
    }
    else {
      prefs.phrase = quoteText(qstate);
    }
    if (gCurrentIdentity.composeHtml) 
      prefs.phrase = postprocessPhrase(prefs.phrase);
	  
	 // inserted by sunfish  - FINAL NEW LINE
      prefs.phrase = newLine(prefs.phrase);
     // end of insert  
  }
  catch(ex) {
    alert("222222222222222 "+ex.message);
  }
}

 // inserted by sunfish  - NEW LINE FUNCTION
function newLine(phrase){
	
	if (phrase.indexOf("%n")!=-1)  {
		
		phrase = phrase.replace(/()?%n( )?/g, "%n");
		var lines = phrase.split("%n");
		var temp = '';
		for (i=0; i<lines.length; i++) 
		{
			temp += lines[i]+"\n";	
		}
	    phrase = temp.replace(/\n$/g, "");	
	    
    }
	return phrase;
}
// end of insert


function quoteText(qstate) {
  var splitted = prefs.phrase.split("\n");
  var qs = prefs.qs;
  var qs2 = prefs.qs2;
  var newphr = "",i;
  var lastline = splitted.length-qstate[1];
  var firstline = qstate[0];
  for (i=0; i<splitted.length; i++) {
    if (i>=firstline && i<lastline)
      newphr+=(qs+splitted[i]+qs2+"\n");
    else
      newphr+= splitted[i]+"\n";
  }
  return newphr;
  /*var startIdx = 0,dimSegm;
  var newphr = "",segment, cont = true;
  do {
    dimSegm = toquote.indexOf("\n",startIdx)-startIdx;
    if (dimSegm<0) {
      dimSegm = prefs.phrase.length-startIdx;
      cont = false;
    }
    segment = prefs.phrase.substr(startIdx,dimSegm);
    startIdx+=dimSegm+1;
    newphr += (prefs.qs+segment+"\n");
  }
  while(cont);  */
  
}

function rewrap(qstate) {
  var s = prefs.phrase;
  var tWidth = prefs.wc;
  var qs = prefs.qs;
  var breakStr = prefs.qs2+"\n";
  var newString="", begin = "", i, lines=s.split("\n"),wc = tWidth+qs.length;
  try{
  var lastline = lines.length-qstate[1];
  var firstline = qstate[0];
  var normtWidth = tWidth-qs.length-breakStr.length+1;
  var sptWidth = tWidth;
  for(i=0;i<lines.length; i++){
    if (i>=firstline && i<lastline)
      tWidth = normtWidth;
    else
      tWidth = sptWidth;
    if(lines[i].length>tWidth){
      var str= lines[i];
      while(str.length>tWidth){
        var pos = getLastSpaceIndex(str.substr(0, tWidth));
          if (pos == -1) {
            pos = getFirstSpaceIndex(str)
            if (pos ==-1)
              break;
          }
          pos++;
          if (i>=firstline && i<lastline) {
            begin = qs+str.substr(0,pos);
            begin = insertBreak(begin,breakStr,wc);
          }
          else
            begin = str.substr(0,pos)+"\n";
          newString+=begin;
          str=str.substr(pos,str.length-pos);
      }
      if (i>=firstline && i<lastline) {
        begin = qs+str;
        begin = insertBreak(begin,breakStr,wc);
      }
      else
        begin = str+"\n";
      newString+=begin;
    }
    else{
      if (i>=firstline && i<lastline) {
        begin = qs+lines[i];
        begin = insertBreak(begin,breakStr,wc);
      }
      else
        begin = lines[i]+"\n";
      newString+=begin;
    }
  }
  }catch(ex) {alert(ex.message);}
  return newString; 
}

function insertBreak(begin, end, wc) {
  if (gCurrentIdentity.composeHtml || begin.length>=wc || end=="\n") {
    return begin+end;
  }
  else {
    var i;
    wc-=begin.length;
    var arr = begin.match(/\t/gi);
    if (arr!=null && arr.length>0)
      wc-=(arr.length*3);
    for (i=0; i<wc; i++) {
      begin+=' ';
    }
    return begin+end;
  }
}

function getLastSpaceIndex(s) {
  var lsi = s.length-1;
  while(lsi>=0) {
    if (s.charAt(lsi)==' ' || s.charAt(lsi)=='\t' || s.charAt(lsi)=='\0' || s.charAt(lsi)=='\r' || s.charAt(lsi)=='\v') {
      return lsi;
    }
    lsi--;
  }
  return -1;
}

function getFirstSpaceIndex(s) {
  var lsi = 0;
  while(lsi<s.length) {
    if (s.charAt(lsi)==' ' || s.charAt(lsi)=='\t' || s.charAt(lsi)=='\0' || s.charAt(lsi)=='\r' || s.charAt(lsi)=='\v') {
      return lsi;
    }
    lsi++;
  }
  return -1;
}

function replaceAll(a) {
  if (a.indexOf("%author")!=-1 || a.indexOf("%email")!=-1)
    parseAuthorNameAndEmailAddress();
  if (a.indexOf("%date")!=-1 || a.indexOf("%time")!=-1)
    parseDateAndTime();
  a = a.replace(/%author/gi, prefs.aname);
  a = a.replace(/%date/gi, prefs.date);
  a = a.replace(/%time/gi, prefs.time);
  arr = a.match(/\{[^\}]{0,}%news[^\}]{0,}\}/gi);
  if (arr!=null) {
    for (i=0; i<arr.length; i++) {
      if (prefs.news!="") {
        a = a.replace(arr[i],arr[i].substr(1,arr[i].length-2));
      }
      else {
        a = a.replace(arr[i],"");
      }
    }
  }
  a = a.replace(/%news/gi,getNewsgroup());
  a = a.replace(/%id/gi,prefs.id);
  a = a.replace(/%email/gi,prefs.aemail);
  return a.replace(/%subject/gi,prefs.subj);
}

function getNewsgroup() {
	  var lio = prefs.news.lastIndexOf("/")+1;
	  return prefs.news.substr(lio,prefs.news.length-lio);  
}

function parseAuthorNameAndEmailAddress() {
  var auth = prefs.to;
  var strippedAddresses = auth.replace(/.* >> /, "");
  var hdrParser = Components.classes["@mozilla.org/messenger/headerparser;1"].getService(Components.interfaces.nsIMsgHeaderParser);
  var addresses = {};
  var names = {};
  var fullNames = {};
  var numAddresses = hdrParser.parseHeadersWithArray(strippedAddresses, addresses, names, fullNames);
  if (numAddresses>0) {
    if (names.value[0]!="")
      prefs.aname = names.value[0];
    else if (addresses.value[0]!="") 
      prefs.aname = addresses.value[0];
    else
      prefs.aname = fullNames.value[0];
    if (addresses.value[0]!=null) 
      prefs.aemail = addresses.value[0];
  } 
}

function parseDateAndTime() {
  var d = new Date(+prefs.lng);
  var dateFormatService = Components.classes["@mozilla.org/intl/scriptabledateformat;1"].getService(Components.interfaces.nsIScriptableDateFormat);
  prefs.date = dateFormatService.FormatDate("", 
                                                  dateFormatService.dateFormatShort, 
                                                  d.getFullYear(), 
                                                  d.getMonth()+1, 
                                                  d.getDate());  
  prefs.time = dateFormatService.FormatTime("", 
                                                  dateFormatService.timeFormatNoSeconds, 
                                                  d.getHours(), 
                                                  d.getMinutes(), 
                                                  d.getSeconds());
}
