var _tCh = false;
function sys_spin() {
    
};
function save_sys(){
    console.log("Saving...");
};

/** Load Current settings: **/
function load_sys(){
      $.getJSON("api/settings.json",function(data){
        var ipaddr = data.sys.ip.ip_1+"."+data.sys.ip.ip_2+"."+data.sys.ip.ip_3+"."+data.sys.ip.ip_4;
        $("#ipv4_ad").val(ipaddr);
        ipaddr = data.sys.ip.nm_1+"."+data.sys.ip.nm_2+"."+data.sys.ip.nm_3+"."+data.sys.ip.nm_4;
        $("#ipv4_nm").val(ipaddr);
        ipaddr = data.sys.ip.gw_1+"."+data.sys.ip.gw_2+"."+data.sys.ip.gw_3+"."+data.sys.ip.gw_4;
        $("#ipv4_gw").val(ipaddr);
        ipaddr = data.sys.ip.dn_1+"."+data.sys.ip.dn_2+"."+data.sys.ip.dn_3+"."+data.sys.ip.dn_4;
        $("#ipv4_dn").val(ipaddr);
        
        $("#time").val(data.sys.currtime.time);
        $("#date").val(data.sys.currtime.date);
       
        sys_wifimode();
        sys_ipmode();
    });
}

/** Scan for Wifi APs **/
function sys_scan() { 
    sys_scan_mod = new bootstrap.Modal($("#sys_scanning"));
    sys_scan_mod.show();
    $("#ssid").empty();
    var option = new Option("--- SCANNING ---", 0); $('#ssid').append($(option));
    option.selected = true;
    $.getJSON("api/networks.json",function(data){
//         console.log(data.sys.ssids[0]);
        $("#ssid").empty();
        for (i in data.sys.ssids)  {
            ssid = data.sys.ssids[i];
            var option = new Option(ssid.n+" (Signal: "+ssid.s+")", ssid.i); $('#ssid').append($(option));
        };

        
    });
};

/** Add (hidden) Network to list **/
function sys_addnw() {
    sys_add_mod = new bootstrap.Modal($("#sys_addnw"));
    sys_add_mod.show();
};

/** Display/Change the SoftAP SSID **/
function sys_softnw() {
    
};

/** WIFI Mode toggle : **/
function sys_wifimode() {
  var mod = $("#wifim")[0].value;
  if (mod  == 'a') {
      $("#ssid")[0].disabled = true;
      $("#ssid")[0].options[0].selected = true;
    } else {
      $("#ssid")[0].disabled = false;
    };
};
/** WiFi add AP: **/
function sys_addnet() {
     var net = $("#new_ssid")[0].value;
     var option = new Option(net+" (Signal: Unknown)", net); $('#ssid').append($(option));
};

/** IPv4 Mode Toggle: **/
function sys_ipmode() {
  var mod = $("#ipv4_m")[0].value;
  if (mod  == 'd') {
      $("#ipv4_ad")[0].disabled = true;
      $("#ipv4_nm")[0].disabled = true;
      $("#ipv4_gw")[0].disabled = true;
      $("#ipv4_dn")[0].disabled = true;

    } else {
      $("#ipv4_ad")[0].disabled = false;
      $("#ipv4_nm")[0].disabled = false;
      $("#ipv4_gw")[0].disabled = false;
      $("#ipv4_dn")[0].disabled = false;
    };  
};
load_sys();
