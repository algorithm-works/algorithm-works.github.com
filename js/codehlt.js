/**
 * the file is previously an utility for highlighting code and was included by all files but now works as a loading point.
 */
requirejs.config({
   paths:{
      'ace':'acesrc/ace'
   },
   shim:{
      'ace':{
         exports:'ace',
      }
   }
});
require(['ace',"zlib/zlibmain"],function(ace,zlib){
   window.highlightPrefix = "qxcode";
   window.hltSuf = 0;
   window.editors = [];
   window.defaultMode = "ace/mode/javascript";
   window.defaultTheme = "ace/theme/solarized_light";
   window.qset = {};

   window.hltElement = function hltElement(p) {
      editors.push(ace.edit(p.id));
      var le = editors[editors.length - 1];
      var themex = p.dataset["theme"] ? p.dataset["theme"] : defaultTheme;
      le.setTheme(themex);
      var modex = p.dataset["mode"] ? p.dataset["mode"] : defaultMode;
      le.getSession().setMode(modex);
      le.setReadOnly(true);
      le.setOption("fontSize", "16px");
      le.setOption("showPrintMargin", false);
      le.setOption("tabSize", 3);
      le.setOption("useSoftTabs", true);
      p.setAttribute("data-ace-nth", editors.length - 1);
      if (p.dataset["ace_conf"]) {
         var cnf = JSON.parse(p.dataset["ace_conf"]);
         le.setOptions(cnf);
      }
   }

   window.enableCodeEdit = function enableCodeEdit(p) { //a helper function for furthur development
      editors.push(ace.edit(p.id));
      var le = editors[editors.length - 1];
      var themex = p.dataset["theme"] ? p.dataset["theme"] : defaultTheme;
      le.setTheme(themex);
      var modex = p.dataset["mode"] ? p.dataset["mode"] : defaultMode;
      le.getSession().setMode(modex);
      le.setOption("fontSize", "16px");
      le.setOption("showPrintMargin", false);
      le.setOption("useSoftTabs", true);
      le.setOption("tabSize", 3);
      p.setAttribute("data-ace-nth", editors.length - 1);
      if (p.dataset["ace_conf"]) {
         var cnf = JSON.parse(p.dataset["ace_conf"]);
         le.setOptions(cnf);
      }
      return [p, le];
   }

   window.qrender = function qrender(qqxi) {
      if (qqxi.dataset["height"]) qqxi.style.height = qqxi.dataset["height"];
      if (qqxi.dataset["width"]) qqxi.style.width = qqxi.dataset["width"];
      hltElement(qqxi);
      if (qqxi.dataset["edit"] == "edit") editors[editors.length - 1].setReadOnly(false);
   }

   window.highlightAllWithACE = function highlightAllWithACE() {
      var qqx = document.querySelectorAll("pre.codehlt");
      ++hltSuf;
      for (var i = 0; i < qqx.length; ++i) {
         if (qqx[i].dataset["delay_render"] == "delay") continue;
         if (!qqx[i].id) qqx[i].id = highlightPrefix + '_' + i + '_' + hltSuf;
         if (qqx[i].dataset["height"]) qqx[i].style.height = qqx[i].dataset["height"];
         if (qqx[i].dataset["width"]) qqx[i].style.width = qqx[i].dataset["width"];
         hltElement(qqx[i]);
         if (qqx[i].dataset["edit"] == "edit") editors[editors.length - 1].setReadOnly(false);
      }
   }

   highlightAllWithACE();

   window.zlibSession.setup();
});
