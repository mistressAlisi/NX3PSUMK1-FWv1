var spec_preset = [];
var b_umol = 1941;
var r_umol = 1497;
var g_umol = 1227;
var f_umol = 135;
function updateDash() {
    $.ajax({"url":"/api/spec/profile.csv",
            "crossDomain":true  
            }).done(function( data ){
                var cut_string = data.split(",");  
                spec_preset = {"n":cut_string[0],"s":cut_string[1],"b":((cut_string[2]))/100,"g":((cut_string[4]))/100,"r":((cut_string[3]))/100,"f":((cut_string[5]))/100};
                $("#umol_db")[0].innerHTML = Math.round(spec_preset["b"]*b_umol);
                $("#umol_dr")[0].innerHTML = Math.round(spec_preset["r"]*r_umol);
                $("#umol_gr")[0].innerHTML = Math.round(spec_preset["g"]*g_umol);
                $("#umol_fr")[0].innerHTML = Math.round(spec_preset["f"]*f_umol);
                $("#umol_sig")[0].innerHTML = Math.round((spec_preset["b"]*b_umol)+(spec_preset["r"]*r_umol)+(spec_preset["g"]*g_umol)+(spec_preset["f"]*f_umol));
               $("#p_name")[0].innerHTML =  cut_string[0]; 
               $("#p_b")[0].innerHTML = Math.round(spec_preset["b"]*100);
               $("#p_r")[0].innerHTML = Math.round(spec_preset["r"]*100);
               $("#p_g")[0].innerHTML = Math.round(spec_preset["g"]*100);
               $("#p_f")[0].innerHTML = Math.round(spec_preset["f"]*100);
            });
            
        $.ajax({"url":"/api/sensors/conn.csv",
            "crossDomain":true  
            }).done(function( data ){
                var cut_string = data.split(",");  
               $("#w_mo")[0].innerHTML =  cut_string[0];
               $("#w_ne")[0].innerHTML =  cut_string[1];
               $("#w_si")[0].innerHTML =  cut_string[2]; 
               $("#w_ip")[0].innerHTML =  cut_string[3]; 
               $("#w_me")[0].innerHTML =  cut_string[4]; 

            });
        $.ajax({"url":"/api/sensors/power.csv",
            "crossDomain":true  
            }).done(function( data ){
                var cut_string = data.split(",");  
               $("#s_vi")[0].innerHTML =  cut_string[0];
               $("#s_t1")[0].innerHTML =  cut_string[1];
               $("#s_t2")[0].innerHTML =  cut_string[2]; 
               $("#s_t3")[0].innerHTML =  cut_string[3]; 
               $("#s_fa")[0].innerHTML =  cut_string[4]; 

            });
};

updateDash();
window.dashInt = window.setInterval(updateDash,30000);
