window.dashInt = false;
function db_load(mod,ev){
    if (window.dashInt != false) {
        window.clearInterval(window.dashInt);
        window.dashInt = false;
    };
    $("#db_panel" ).load( "db/"+mod+".html" );
    $("#db_title").text(ev.target.text);
};

function db_sethdr(){
    $.getJSON("api/hdr.json",function(data){
        $("#dash_hdr_ip").text(data.sys.ip);
        $("#dash_hdr_mac").text(data.sys.mac);
        $("#dash_hdr_time").text(data.sys.time);
    });
}
db_sethdr();
$("#db_panel" ).load( "db/dash.html" );
window.hdrint = window.setInterval(db_sethdr,60000);
