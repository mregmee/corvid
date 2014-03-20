var gRDF = Components.classes["@mozilla.org/rdf/rdf-service;1"].getService(Components.interfaces.nsIRDFService);
var RootFolderUriMark = "RootFolderUri";
function getSelectedServerForFilters() {
    var firstItem = null;
    return firstItem;
    var args = window.arguments;
    var selectedFolder = args[0].folder;
    
    if (args && args[0] && selectedFolder) {
        var msgFolder = selectedFolder.QueryInterface(Components.interfaces.nsIMsgFolder);
        try {
            var rootFolder = msgFolder.server.rootFolder;
            if (rootFolder.isServer) {
                var server = rootFolder.server;
                
                if (server.canHaveFilters) {
                    // for news, select the news folder
                    // for everything else, select the folder's server
                    firstItem = (server.type == "nntp") ? msgFolder.URI : rootFolder.URI;
                }
            }
        }
        catch (ex) {
        }
    }
    
    return firstItem;
}
/** if the selected server cannot have filters, get the default server
 * if the default server cannot have filters, check all accounts
 * and get a server that can have filters.
 */
function getServerThatCanHaveFilters() {
    var firstItem = null;
    
    var accountManager
    = Components.classes["@mozilla.org/messenger/account-manager;1"].
    getService(Components.interfaces.nsIMsgAccountManager);
    
    var defaultAccount = accountManager.defaultAccount;
    var defaultIncomingServer = defaultAccount.incomingServer;
    
    // check to see if default server can have filters
    if (defaultIncomingServer.canHaveFilters) {
        firstItem = defaultIncomingServer.serverURI;
    }
    // if it cannot, check all accounts to find a server
    // that can have filters
    else {
        var allServers = accountManager.allServers;
        var numServers = allServers.Count();
        var index = 0;
        for (index = 0; index < numServers; index++) {
            var currentServer
            = allServers.GetElementAt(index).QueryInterface(Components.interfaces.nsIMsgIncomingServer);
            
            if (currentServer.canHaveFilters) {
                firstItem = currentServer.serverURI;
                break;
            }
        }
    }
    
    return firstItem;
}


var filtersimportexport = {
    strbundle: null,
    onLoad: function() {
        // initialization code
        this.initialized = true;
        
    },
    getString:function (name)
    {
	try{
		
		if (this.strbundle == null)
			this.strbundle = document.getElementById("filtersimportexportStrings");
		return this.strbundle.getString(name);
	}catch(e)
	{
		alert(name + " " + e);
		return "";
	}
    },
    onAccountLoad: function() {
        // initialization code
        var firstItem = getSelectedServerForFilters();
        
        // if the selected server cannot have filters, get the default server
        // if the default server cannot have filters, check all accounts
        // and get a server that can have filters.
        if (!firstItem)
            firstItem = getServerThatCanHaveFilters();
        
        if (firstItem) {
            var serverMenu = document.getElementById("serverMenu");
            //alert(firstItem);
            serverMenu.setAttribute("uri",firstItem);
            
        }
        
        
    },
    
    onFilterServerClick: function(selection) {
        //alert(selection);
        var itemURI = selection.getAttribute('id');
        var serverMenu = document.getElementById("serverMenu");
        //alert(itemURI);
        serverMenu.setAttribute("uri",itemURI);
    },
    
    onMenuItemCommand: function() {
        window.open("chrome://filtersimportexport/content/FilterImEx.xul", "", "chrome,centerscreen");
    },
    onImportFilter: function() {
        var serverMenu = document.getElementById("serverMenu");
        var msgFilterURL=serverMenu.getAttribute("uri");
        
        //alert(msgFilterURL);
        var resource = gRDF.GetResource(msgFilterURL);
        var msgFolder = resource.QueryInterface(Components.interfaces.nsIMsgFolder);
        
        
        // this will get the deferred to account root folder, if server is deferred
        msgFolder = msgFolder.server.rootMsgFolder;
        var rootFolderUri = msgFolder.URI;
        
        //alert(rootFolderUri);   
        var filterList = this.currentFilterList(msgFilterURL);
        filterList.saveToDefaultFile();
        //    for (var i = 0; i < filterList.filterCount; i++) 
        //      alert (filterList.getFilterAt(i).filterName);
        
        var filepath=this.selectFile(Components.interfaces.nsIFilePicker.modeOpen);
        var inputStream = this.openFile(filepath.path);
        
        var sstream = Components.classes["@mozilla.org/scriptableinputstream;1"]
        .createInstance(Components.interfaces.nsIScriptableInputStream);
        sstream.init(inputStream); 
        
        var str = sstream.read(4096);
        var data="";
        
        while (str.length > 0) {
            data += str;
            str = sstream.read(4096);
        }
        sstream.close();
        inputStream.close();
	if (data.substr(0,RootFolderUriMark.length) != RootFolderUriMark)
	{
		alert(this.getString("importfailed"));
		return;
	}
	var oldFolderRoot = data.substr(RootFolderUriMark.length + 1,data.indexOf("\n") - data.indexOf("=") -1);
        data = data.substr(data.indexOf("\n")+1);

        var reg = new RegExp(RootFolderUriMark,"g");
        s = data.replace(reg,msgFilterURL);
        //alert(s);
        var stream = this.createFile(filterList.defaultFile.nativePath);
        stream.write(s,s.length);
        stream.close();
	var confirmStr = "";
	if (oldFolderRoot != msgFilterURL)
	    confirmStr = this.getString("finishwithwarning");
	else	
	    confirmStr =this.getString("importfinish");
	
	if (confirm(confirmStr + this.getString("restartconfrim")))
	{
		var nsIAppStartup = Components.interfaces.nsIAppStartup;
		Components.classes["@mozilla.org/toolkit/app-startup;1"].getService(nsIAppStartup).quit(nsIAppStartup.eForceQuit | nsIAppStartup.eRestart);
	}
	else
	   alert(this.getString("restartreminder"));
    },
    onExportFilter: function() {
        var serverMenu = document.getElementById("serverMenu");
        var msgFilterURL=serverMenu.getAttribute("uri");
        
        var resource = gRDF.GetResource(msgFilterURL);
        var msgFolder = resource.QueryInterface(Components.interfaces.nsIMsgFolder);
        
        //Calling getFilterList will detect any errors in rules.dat, backup the file, and alert the user
        //we need to do this because gFilterTree.setAttribute will cause rdf to call getFilterList and there is 
        //no way to pass msgWindow in that case. 
        
        if (msgFolder)
            msgFolder.getFilterList(gFilterListMsgWindow);
        
        // this will get the deferred to account root folder, if server is deferred
        msgFolder = msgFolder.server.rootMsgFolder;
        var rootFolderUri = msgFolder.URI;
        
        //alert(rootFolderUri);   
        var filterList = this.currentFilterList(msgFilterURL);
        filterList.saveToDefaultFile();
        //    for (var i = 0; i < filterList.filterCount; i++) 
        //      alert (filterList.getFilterAt(i).filterName);
        
        var filepath=this.selectFile(Components.interfaces.nsIFilePicker.modeSave);
        var stream = this.createFile(filepath.path);
        var inputStream = this.openFile(filterList.defaultFile.nativePath);
        
        var sstream = Components.classes["@mozilla.org/scriptableinputstream;1"]
        .createInstance(Components.interfaces.nsIScriptableInputStream);
        sstream.init(inputStream); 
        
        var str = sstream.read(4096);
        var data="";
        while (str.length > 0) {
            data += str;
            str = sstream.read(4096);
        }
        
        sstream.close();
        inputStream.close();
        
        var reg = new RegExp(msgFilterURL,"g");
        s = data.replace(reg,RootFolderUriMark);
        //alert(s);
	var mark="RootFolderUri=" + msgFilterURL + "\n";
	stream.write(mark,mark.length);
        stream.write(s,s.length);
        stream.close();
        
    },
    selectFile: function (mode) {
        var fp = Components.classes["@mozilla.org/filepicker;1"]
        .createInstance(Components.interfaces.nsIFilePicker);
        
        
        var title = this.getString("exporttitle");
	if (mode == Components.interfaces.nsIFilePicker.modeOpen)
	    title = this.getString("importtitle");
        fp.init(window, title, mode);
        fp.appendFilters(Components.interfaces.nsIFilePicker.filterAll);
        
        
        var ret = fp.show();
        if (ret == Components.interfaces.nsIFilePicker.returnOK || 
        ret == Components.interfaces.nsIFilePicker.returnReplace) {
            return  fp.file;
        }
    },
    createFile :function (aPath) {
        if (! netscape.security.PrivilegeManager) return null;
        netscape.security.PrivilegeManager
        .enablePrivilege("UniversalFileAccess UniversalXPConnect");
        
        var file=Components.classes["@mozilla.org/file/local;1"]
        .createInstance(Components.interfaces.nsILocalFile);
        file.initWithPath(aPath);
        
        var fileStream = Components.classes['@mozilla.org/network/file-output-stream;1']
        .createInstance(Components.interfaces.nsIFileOutputStream);
        fileStream.init(file, 0x02 | 0x08 | 0x20, 0664, 0);
        return fileStream;
    },
    openFile :function (aPath) {
        if (! netscape.security.PrivilegeManager) return null;
        netscape.security.PrivilegeManager
        .enablePrivilege("UniversalFileAccess UniversalXPConnect");
        
        var file=Components.classes["@mozilla.org/file/local;1"]
        .createInstance(Components.interfaces.nsILocalFile);
        file.initWithPath(aPath);
        
        var fileStream = Components.classes['@mozilla.org/network/file-input-stream;1']
        .createInstance(Components.interfaces.nsIFileInputStream);
        fileStream.init(file, 0x01, 0664, 0);
        return fileStream;
    },
    currentFilterList: function(serverUri) {
        // note, serverUri might be a newsgroup
        var filterList = gRDF.GetResource(serverUri).GetDelegate("filter", Components.interfaces.nsIMsgFilterList);
        return filterList;
    },
    overlayDialog:function() {
	window.removeEventListener("load", filtersimportexport.overlayDialog, false); 
        
        var exportButton = document.getElementById("exportBurron");
        var importButton = document.getElementById("importButton");
        var vboxElement = document.getElementById("newButton").parentNode;

        // Append them to the end of the button box
        vboxElement.appendChild(exportButton);
        //	vboxElement.appendChild(importButton);
    }
};

//window.addEventListener("load", function(e) { filtersimportexport.onLoad(e); }, false); 
