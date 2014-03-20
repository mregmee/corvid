var str;
var strLength;


//function openWindow(prefs) {
//  try {
//  var folder = GetFirstSelectedMsgFolder();
//  var messageArray = GetSelectedMessages();
//  var msgComposeType = Components.interfaces.nsIMsgCompType;
//  var type = msgComposeType.ReplyToSender;
//	var identity = null;
//	var newsgroup = null;
//	var format = msgComposeFormat.Default;
//	var server;  
//  try {
//		if(folder) {
//			// get the incoming server associated with this uri
//			server = folder.server;
//			// if they hit new or reply and they are reading a newsgroup
//			// turn this into a new post or a reply to group.
//      if (!folder.isServer && server.type == "nntp") {
//        if (type == msgComposeType.New) {
//          type = msgComposeType.NewsPost;
//          newsgroup = folder.folderURL;
//			  }
//			  else if (prefs.operation==NEWS) {
//			    type = msgComposeType.ReplyToGroup;
//			  }
//      // dump("identity = " + identity + "\n");
//      }
//      identity = getIdentityForServer(server);
//		}
//	}
//	catch (ex) {
//    dump("failed to get an identity to pre-select: " + ex + "\n");
//	}
//	if (type == msgComposeType.NewsPost) {
//	  prefs.news = newsgroup.toString();
//	  var lio = prefs.news.lastIndexOf("/")+1;
//	  prefs.news = prefs.news.substr(lio,prefs.news.length-lio);
//    prefs.saveTmp();	  
//		msgComposeService.OpenComposeWindow(null, newsgroup, type, format, identity, msgWindow);
//		return;
//	}
//	messenger.SetWindow(window, msgWindow);			
//	var object = null;
//	if (messageArray && messageArray.length > 0) {
//	  for (var i = 0; i < messageArray.length; i ++)  {	
//			var messageUri = messageArray[i];
//      var hdr = messenger.messageServiceFromURI(messageUri).messageURIToMsgHdr(messageUri);
//      var hintForIdentity = hdr.recipients + hdr.ccList;
//      if (folder)
//        server = folder.server;
//      if (server)
//        identity = getIdentityForServer(server, hintForIdentity);
//      if (!identity || hintForIdentity.search(identity.email) < 0) {
//        var accountKey = hdr.accountKey;
//        if (accountKey.length > 0) {
//          var account = accountManager.getAccount(accountKey);
//          if (account) {
//            server = account.incomingServer;
//            if (server)
//              identity = getIdentityForServer(server, hintForIdentity);
//          }
//        }
//      }
//	    prefs.saveTmp();      
//      msgComposeService.OpenComposeWindow(null, messageUri, prefs.operation==REPLYALL?msgComposeType.ReplyAll:type, format, identity, msgWindow);
//    }
//  }
//  }catch(ex) { alert("errore "+ex.toString());}
//}

function quickquote(event,prefs) {
  try {
    if (prefs==null) {
      prefs = new quickquotePrefs();
      prefs.load();
    }
    prefs.operation = REPLY;
    if (event.target == document.getElementById("quickquote_news") || (event.type=="keypress" && 
             String.fromCharCode(event.which)==document.getElementById("quickquote_news_k").getAttribute("key"))) {
      prefs.operation = NEWS;
    }
    else if (event.target == document.getElementById("quickquote_new") || (event.type=="keypress" && 
             String.fromCharCode(event.which)==document.getElementById("quickquote_new_k").getAttribute("key"))) {
      prefs.operation = NEWMSG;
    }
    else if (event.target == document.getElementById("quickquote_replyall") || 
            event.target == document.getElementById("button-replyall") ||
            (event.type=="keypress" && 
             String.fromCharCode(event.which)==document.getElementById("quickquote_replyall_k").getAttribute("key"))) {
      prefs.operation = REPLYALL;
    }
    else if (event.target == document.getElementById("quickquote_comp") || 
            (event.type=="keypress" && 
             String.fromCharCode(event.which)==document.getElementById("quickquote_comp_k").getAttribute("key"))) {
      prefs.operation = CURRMSG;
    }  
    if (prefs.work!=GET_SEL) {
	    document.getElementById('messagepane').contentViewerEdit.copySelection();
	    getClipboardContents(prefs.work==PASTE?"html":"unicode");
	    prefs.phrase = convertToString();
	  }
	  else {
      prefs.phrase = getSelectedString();
	  }
	  if (prefs.operation!=CURRMSG)
	    parseMsgProperties(GetSelectedMessages()[0],prefs);
	  prefs.saveTmp();
	  switch (prefs.operation) {
	    case NEWMSG:
	      MsgNewMessage(null);
	      break;
	    case REPLY:
	      MsgReplySender(event);
	      break;
	    case REPLYALL:
	      MsgReplyToAllMessage(event);
	      break;
	    case NEWS:
	      MsgReplyGroup(event);
	      break;	    
	  }
  }
  catch(ex){
    alert("TTTTTTTTTTTTTTTTTTT "+ex.message);
  }
}

function toolbarPaletteAction(event) {
  var prefs = null;
  var getText=document.getElementById('messagepane').contentWindow.getSelection();
  var tS = getText!=null && getText.toString().length>0;
  if (event.target==document.getElementById("button-reply")) {
    if (tS) {
      prefs = new quickquotePrefs();
      prefs.load();
      if (prefs.quotereply) {
        quickquote(event,prefs);
        return;
      }
    }
    MsgReplyMessage(event);    
  }
  else {
    if (tS) {
      prefs = new quickquotePrefs();
      prefs.load();
      if (prefs.quotereplyall) {
        quickquote(event,prefs);
        return;
      }
    }
    MsgReplyToAllMessage(event);
  }
}

function getSelectedString() {
  var focusedWindow = document.commandDispatcher.focusedWindow;
  /*var sel = focusedWindow.getSelection.call(focusedWindow);
  var messageDocument = document.getElementById('messagepane').contentDocument;
  var qno = messageDocument.getElementsByTagName("blockquote").item(0);
  if (qno!=null) {
    alert("presente "+qno.tagName+" "+qno.hasChildNodes());
    var qn = sel.getRangeAt(0).cloneContents();
    for (var i=0; i<qno.childNodes.length; i++) {
      for (var j=0; j<qno.childNodes.length; j++) {
        if (qn.childNodes.item(i).isSameNode(qno.childNodes.item(j))) 
          alert("evvai: "+" | "+qn.childNodes.item(i).nodeValue+" | "+qn.childNodes.item(i).tagName+" | "+qn.childNodes.item(i).textContent);
      }
      alert(i+" | "+qno.childNodes.item(i).nodeValue+" | "+qno.childNodes.item(i).tagName+" | "+qno.childNodes.item(i).innerHTML+" | ");
    }
    if (sel.containsNode(qno,true)) {
      alert("quotation node");
    }
  }*/
	return focusedWindow.getSelection.call(focusedWindow).toString();
	
}

function quickquote_init() {
  var oContext = document.getElementById('messagepane');
  if (oContext!=null) {
    oContext.addEventListener("load",onMessagePaneLoad,true);
  }
}

function onMessagePaneLoad() {
  var tpb = document.getElementById("button-reply");
  if (tpb!=null) {
    tpb.setAttribute("oncommand","toolbarPaletteAction(event);");
  }    
  var tpb = document.getElementById("button-replyall");
  if (tpb!=null) {
    tpb.setAttribute("oncommand","toolbarPaletteAction(event);");
  }   
  var oContext = document.getElementById('messagePaneContext');
  if (oContext!=null) {
    oContext.addEventListener("popupshowing",quickquote_collapse_if_necessary,true);
  }
}

function hideMenus() {
  var msg = GetSelectedMessages();
  if (msg!=null && msg.length>0) {
    var getText=document.getElementById('messagepane').contentWindow.getSelection();
    return val = (getText==null || getText.toString().length==0);
  }
  else
    return true;
}

function quickquote_collapse_if_necessary() {
  try {
    if (gContextMenu) {
      var val = hideMenus();
      var mn = document.getElementById('quickquote_new');      
      if (mn!=null)
        mn.hidden = val;
      mn = document.getElementById('quickquote_reply');
      if (mn!=null)
        mn.hidden = val;
      mn = document.getElementById('quickquote_replyall');
      if (mn!=null)
        mn.hidden = val;        
      mn = document.getElementById('quickquote_menusep');
      if (mn!=null)
        mn.hidden = val;      
      mn = document.getElementById('quickquote_comp');      
      if (mn!=null)
        mn.hidden = val;        
      mn = document.getElementById('quickquote_menusep2');
      if (mn!=null)
        mn.hidden = val;      
      mn = document.getElementById('quickquote_news');
      if (mn!=null) {
        if (!val) {
          val = !IsNewsMessage(GetSelectedMessages()[0]);
        }
        mn.hidden = val;
      }        
    }
  }
  catch(ex){alert(ex.message);}
}

function parseMsgProperties(m,prefs) {
  var hdr = messenger.messageServiceFromURI(m).messageURIToMsgHdr(m);
  if (hdr.date!=null) {
    var str = hdr.date+"";
    str = str.substring(0,str.length-3);
    prefs.lng = str;
  }
  if (hdr.messageId!=null)
    prefs.id = hdr.messageId;
  if (hdr.mime2DecodedSubject!=null) 
    prefs.subj = hdr.mime2DecodedSubject;
  if (hdr.mime2DecodedAuthor!=null)
    prefs.to = hdr.mime2DecodedAuthor;
  var folder = GetFirstSelectedMsgFolder();
  if (folder && !folder.isServer && folder.server.type == "nntp") {
    prefs.news = folder.folderURL.toString();
  }
}

function getClipboardContents(flav) {
  var clip = Components.classes["@mozilla.org/widget/clipboard;1"].
             getService(Components.interfaces.nsIClipboard);           
  if (!clip) return false;
  var trans = Components.classes["@mozilla.org/widget/transferable;1"].
              createInstance(Components.interfaces.nsITransferable);
  if (!trans) return false;
  trans.addDataFlavor("text/"+flav);
  clip.getData(trans,clip.kGlobalClipboard);
  str = new Object();
  strLength = new Object();
  try {
    trans.getTransferData("text/"+flav,str,strLength);  
  }
  catch (ex) {
    return false;
  }
  return true; 
}

function convertToString() {
  if (str) str = str.value.QueryInterface(Components.interfaces.nsISupportsString);
  if (str) 
    return str.data.substring(0,strLength.value / 2);
  else 
    return null;  
}
