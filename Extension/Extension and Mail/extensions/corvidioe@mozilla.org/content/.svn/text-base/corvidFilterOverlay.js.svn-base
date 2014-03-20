spamThreshold = 0.9;

var gAserv=Components.classes["@mozilla.org/atom-service;1"].
          getService(Components.interfaces.nsIAtomService);

var columnHandler = 
{
   getCellText:         function(row, col) {
   
   	var messageURI = gDBView.getURIForViewIndex(row);
   	var key = gDBView.getKeyAt(row);
   	var hdr = gDBView.db.GetMsgHdrForKey(key);
   	
   	var retval = hdr.getStringProperty("spamstatus");
   	var tmp=retval;	       
   	
       if (!retval)
      {
      		retval= getSpamProbability(hdr);
      		//alert("Sub:"+hdr.subject+" "+retval);
      		tmp = (retval > spamThreshold)?"Spam":" ";
      		hdr.setProperty("spamstatus",tmp);      	
      		hdr.setProperty("spamvalue",retval);      	
      }
      	
      return tmp;
      
   },
   //getSortStringForRow: function(hdr) { return hdr.getStringProperty("spamstatus");},
   isString:            function() {return true;},

   getCellProperties:   function(row, col, props)
   {
   
         
   },
   getRowProperties:    function(row, props)
   {  
   
   
   },
   getImageSrc:         function(row, col) {return null;},
   getSortLongForRow:   function(hdr) {return 0;}
}

function doOnceLoaded()
{  
  var ObserverService = Components.classes["@mozilla.org/observer-service;1"].getService(Components.interfaces.nsIObserverService);
  
  ObserverService.addObserver(co_CreateDbObserver, "MsgCreateDBView", false);  
}

var co_CreateDbObserver = {
   //Components.interfaces.nsIObserver
  observe: function(aMsgFolder, aTopic, aData)
  {  
     
     addCustomColumnHandler();
     
  }
}


function addCustomColumnHandler() 
{	
   gDBView.addColumnHandler("spamStatusCol", columnHandler);   
}

window.addEventListener("load", doOnceLoaded, false);