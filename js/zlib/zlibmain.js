define(function(require,exports,module){
   var zlib=window.zlib={};
   var session=window.zlibSession={};
   zlib.session=session;
   //allocating an zlib session
   zlib.urlUtilities={};
   (function(_){
      _.getURL=function(){
         return window.location.href;
      }
      _.URLAcc=function(proto,pos){
         this.proto=proto;
         this.pos=pos;
         return this;
      }
      function trimArr(arr){
         while(!arr[arr.length-1].valueOf()) arr.pop();
         return arr;
      }
      _.parseURL=function(){
         var url=_.getURL();
         var urlSplit=url.split('://');

         return new _.URLAcc(urlSplit[0],trimArr(urlSplit[1].split('/')));
      }
      _.URLAcc.prototype.getFather=function(){
         var urlK=[];
         for(var i=0;i<this.pos.length-1;++i) urlK.push(this.pos[i].valueOf());
         return new _.URLAcc(this.proto.valueOf(),urlK);
      }
      _.changeNav=function(str){
         history.replaceState(null,'',str);
      }
   })(zlib.urlUtilities);
   zlib.session.setup=function(){
      zlib.pageURL=zlib.urlUtilities.parseURL();
   }
   exports.zlib=zlib;
   return zlib;
});
