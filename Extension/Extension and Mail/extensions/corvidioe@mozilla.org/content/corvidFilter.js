try 
{
	const cid = "@mozilla.org/corvidioe/Filtration;1";
	obj = Components.classes[cid].createInstance();
	obj = obj.QueryInterface(Components.interfaces.IFiltration);

	var file = Components.classes["@mozilla.org/file/directory_service;1"]
			     .getService(Components.interfaces.nsIProperties)
			     .get("ProfD", Components.interfaces.nsIFile);
	datapath = file.path+"\\extensions\\corvidioe@mozilla.org\\data";
	obj.InitFilter(datapath);
	
	const cids = "@mozilla.org/corvidioe/Summarization;1";
	objs = Components.classes[cids].createInstance();
	objs = objs.QueryInterface(Components.interfaces.ISummarization);
		
	const cidc = "@mozilla.org/corvidioe/Classification;1";
	objc = Components.classes[cidc].createInstance();
	objc = objc.QueryInterface(Components.interfaces.IClassification);
	objc.trainClassification(datapath+"\\classification");
	setPreferences();
} 

catch (err) 
{
	alert(err);
}

function setPreferences()
{
	var prefs = Components.classes["@mozilla.org/preferences-service;1"].getService(Components.interfaces.nsIPrefBranch);

	if(!prefs.prefHasUserValue("corvidioe.filter.spamThreshold"))
		prefs.setIntPref("corvidioe.filter.spamThreshold",95);
		
	if(!prefs.prefHasUserValue("corvidioe.filter.learningRate"))
		prefs.setIntPref("corvidioe.filter.learningRate",5);
	
	if(!prefs.prefHasUserValue("corvidioe.summary.lengthOfSummary"))
		prefs.setIntPref("corvidioe.summary.lengthOfSummary",20);	
}
	
	
function onTrainSummary()
{
	window.open("trainSummary.xul");
}

function onChangeStatus() 
{
	view = GetDBView();
	hdr = view.hdrForFirstSelectedMessage;
	curStatus = hdr.getStringProperty("spamstatus");
	toStatus = curStatus=="Spam"?"ham":"spam";
	toS = curStatus=="Spam"?" ":"Spam";
	
	bodyAndHdr = getEmailString(hdr);
	
	alert('This may take some time as it needs to update the knowledgebase.');
	
	try{
		obj.InitUpdate(datapath);
		obj.UpdateKnowledge(bodyAndHdr,toStatus);
	}
	
	catch(e)
	{
		alert(e);
	}
	

	hdr.setStringProperty("spamstatus",toS);
	
	curStatus = hdr.getStringProperty("spamstatus");
	curStatus2 = (curStatus=="Spam")?"Spam":"Not Spam";
	alert('Spam Status : '+curStatus2);	
}

function onViewSpamValue() 
{
	view = GetDBView();
	hdr = view.hdrForFirstSelectedMessage;
	sv = hdr.getStringProperty("spamvalue");
	alert('Spam Value '+sv);
	
	curStatus = hdr.getStringProperty("spamstatus");
	curStatus2 = (curStatus=="Spam")?"Spam":"Not Spam";
	alert('Spam Status : '+curStatus2);
}

function onClassifyEmail()
{
	view = GetDBView();
	hdr = view.hdrForFirstSelectedMessage;
	category=objc.classifyEmail(getEmailBody(hdr),hdr.subject,datapath+"\\classification");
	alert(category);
	
	alert('Current Category '+hdr.folder.name);
}

function onMoveEmail(category)
{
	view = GetDBView();
	hdr = view.hdrForFirstSelectedMessage;
	objc.learnClassification(getEmailBody(hdr),hdr.subject,category,datapath+"\\classification");
}

function onViewSummary() 
{
	view = GetDBView();
	hdr = view.hdrForFirstSelectedMessage;
	alert(getEmailSummary(hdr));
}


function getSpamProbability(hdr)
{
	bodyAndHdr = getEmailString(hdr);
	return obj.PredictEmail(bodyAndHdr);
}

function getEmailSummary(hdr)
{
	body = getEmailBody(hdr);
	return objs.summarizeEmail(body,datapath);	
}

function getEmailString(hdr)
{
	//initialize input stream for offline messages
	var offset = new Object();
	var messageSize = new Object();
	var is=new Object();
	try
	{
		var folder=hdr.folder;
		//input stream for given message in given folder
		is = folder.getOfflineFileStream(hdr.messageKey,offset,messageSize);
	}
	catch(e)
	{
		alert("message: "+e.message);
	}
	try
	{
		var sis = Components.classes["@mozilla.org/scriptableinputstream;1"].createInstance(Components.interfaces.nsIScriptableInputStream);
		//wrap input stream by scriptable inputstream
		sis.init(is);
		bodyAndHdr = sis.read(hdr.messageSize-10);//get body and hdr in plain text
	}
		
	catch(err)
	{
		alert(err);
	}
	return bodyAndHdr;
}


function getEmailBody(hdr)
{
	bodyAndHdr=getEmailString(hdr);	
	hdrstr = bodyAndHdr.indexOf("\r\n\r\n"); //marks the end of the //headers
	body = bodyAndHdr.substring(hdrstr+1,bodyAndHdr.length);
	
	hdrstr = body.indexOf("Content-Disposition: attachment"); //marks the start of the attachment
	
	if(hdrstr != -1)

	{
		bodyra = body.substring(0,hdrstr);
		return bodyra;
	}
	else
		return body;
}