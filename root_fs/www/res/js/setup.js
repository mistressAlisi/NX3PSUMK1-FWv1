function finalise_setup() {
    $.get( "/api/setup/reboot.json", function( data ) {
        if (data["stat"] == "ok") {
             alert("d9NX3 is applying settings and rebooting.");
        } else {
            alert("Unable to commit:\n"+data["stat"]);
        }
    });
};

function check_step3() {
    var usrpw = $("#upw")[0].value;
    if (usrpw != "") {
        if (usrpw.length < 7) {
            alert("User Password must be 8 characters minimum.");
            return false;
        }
    }
    if (usrpw != $("#upw2")[0].value) {
            alert("User Passwords must be equal.");
            return false;
    };
    var username = $("#username")[0].value;
    if (username.length == "") {
            alert("User cannot be blank.");
            return false;
    };
    conf_data = $("#setup_form").serialize();
    $.post( "/api/setup/commit_user.json",conf_data, function( data ) {
        if (data["stat"] == "ok") {
             $.get( "/setup/step_done.html", function( data ) {
                $("#setup_title")[0].innerHTML = "Setup Complete!";
                $("#setup_card" ).html( data );
                $("#setup_btn")[0].onclick = finalise_setup;
                 $("#setup_btn")[0].innerHTML = "Reboot into User Mode";
            });
        } else {
            alert("Unable to commit:\n"+data["stat"]);
        }
    });
};

function check_step2() {
    var date_time = $("#datetime")[0].value;
    if (date_time == "") {
            alert("Please set current date and time to continue.");
            return false;
    };
    date = $('#datetime').datetimepicker('viewDate');
    $("#DD")[0].value = date.day();
    $("#MM")[0].value = date.month();
    $("#YYYY")[0].value = date.year();
    $("#HH")[0].value = date.hour();
    $("#m")[0].value = date.minute();
    $("#SS")[0].value = date.seconds();
    conf_data = $("#setup_form").serialize();
    $.post( "/api/setup/commit_datetime.json", conf_data,function( data ) {
        if (data["stat"] == "ok") {
             $.get( "/setup/step_3.html", function( data ) {
                $("#setup_title")[0].innerHTML = "Set access credentials:";
                $("#setup_card" ).html( data );
                $("#setup_btn")[0].onclick = false;
                $("#setup_btn")[0].onclick = check_step3;
            });
        } else {
            alert("Unable to commit:\n"+data["stat"]);
        }
    });
};


function check_step1_ap() {
    var wifipw = $("#wifi_ap_pw")[0].value;
    if (wifipw != "") {
        if (wifipw.length < 7) {
            alert("WiFi Password must be 8 characters minimum or blank.");
            return false;
        }
    }
    if (wifipw != $("#wifi_ap_pw2")[0].value) {
            alert("WiFi Passwords must be equal.");
            return false;
    };
    var wifissid = $("#wifi_ap_ssid")[0].value;
    if (wifissid.length == "") {
            alert("WiFi SSID/Name Cannot be blank!!");
            return false;
    };
    conf_data = $("#setup_form").serialize();
    $.post( "/api/setup/commit_apssid.json",conf_data, function( data ) {
        if (data["stat"] == "ok") {
             $.get( "/setup/step_2.html", function( data ) {
                $("#setup_title")[0].innerHTML = "Set date and time:";
                $( "#setup_card" ).html( data );
                $("#setup_btn")[0].onclick = false;
                $("#setup_btn")[0].onclick = check_step2;
            });
        } else {
            alert("Unable to commit:\n"+data["stat"]);
        }
    });
};


function setup_scan() {
    $("#scan_btn")[0].disabled = true;
    $("#scanning")[0].style.display = 'block';
    $.get( "/api/setup/networks.json", function( data ) {
        $("#wifi_ap_ssid").empty();
        for (i in data.sys.ssids)  {
            ssid = data.sys.ssids[i];
            var option = new Option(ssid.n+" (Signal: "+ssid.s+")", ssid.n); $('#wifi_ap_ssid').append($(option));
        };
        $("#scan_btn")[0].disabled = false;
        $("#scanning")[0].style.display = 'none';
    });
};

function setup_addap() {
    var newSSID = prompt("Enter the SSID of the network to join:");
    if (newSSID == null) { return false; };
    var option = new Option(newSSID+" (Signal: N/A)", newSSID); $('#wifi_ap_ssid').append($(option));
    option.selected = true;
};

function check_step1() {
    var sta = $("#wifi_sta")[0].checked;
    var ap = $("#wifi_ap")[0].checked;
    if ((ap == false)&&(sta == false)) {
        alert("Please select AP or Client mode.");
        return false;
    };
    if (ap == true) {
            $("#setup_title")[0].innerHTML = "Enter AP Mode Details:";
             $.get( "/setup/step_1_ap.html", function( data ) {
            $( "#setup_card" ).html( data );
            $("#setup_btn")[0].onclick = false;
            $("#setup_btn")[0].onclick = check_step1_ap;
            $("#setup_btn")[0].innerHTML = 'Next';
            $.get( "/api/setup/default_apssid.json", function( data ) {
                 $("#wifi_ap_ssid")[0].value = data["sys"]["default_ssid"]; 
                });
            });
    } else {
            $("#setup_title")[0].innerHTML = "Select your WiFi Network:";
            $.get( "/setup/step_1_sta.html", function( data ) {
            $( "#setup_card" ).html( data );
            $("#setup_btn")[0].onclick = false;
            $("#setup_btn")[0].onclick = check_step1_ap;
            $("#setup_btn")[0].innerHTML = 'Next';
            $("#dhcp_enabled").on('change',dhcp_toggle);
            $("#setup_form").find('input[type|=number]').attr('disabled', true);
            setup_scan();
        });
    };
    
};

function setup_step1() {
    $("#setup_title")[0].innerHTML = "Select WiFi mode:";
    $.get( "/setup/step_1.html", function( data ) {
        $( "#setup_card" ).html( data );
        $("#setup_btn")[0].onclick = false;
        $("#setup_btn")[0].onclick = check_step1;
        $("#setup_btn")[0].innerHTML = "Next";
    });
};

function db_sethdr(){
    $.getJSON("/api/hdr.json",function(data){
        $("#dash_hdr_ip").text(data.sys.ip);
        $("#dash_hdr_mac").text(data.sys.mac);
    });
}
function dhcp_toggle(){
    if ($("#dhcp_enabled")[0].checked == true) {
        $("#setup_form").find('input[type|=number]').attr('disabled', true);
    } else {
        $("#setup_form").find('input[type|=number]').attr('disabled', false);
    };
};

db_sethdr();

