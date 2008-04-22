<?php
/**
* Marker Handling Page of GPS Module
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Sriganeshan <sri@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $global;
global $conf;
global $file;
$file=$_FILES['load'];
$extentions=array('gpx');
//check weather a file was uploaed
if(isset($file)){
    //get the extention and the tmp name of the file
    $ext=end(explode('.',$_FILES['load']['name']));
    unset($_SESSION['gps']['file']);
    $_SESSION['gps']['file']="./tmp/".basename($_FILES['load']['name']);
    //check for tmp file permision
    if(!is_writable('./tmp')){
        add_error(_('Make sure the tmp folder is writerble'));
    }
 
    //check weather an error occored
    else if($file['error']!= 0){
        //give error information
        switch ($file['error']){
            case 1:
            case 2:
                add_error(_('The uploaded file exceeds the MAX upload size'));
                break;
            case 3:
                add_error(_('The uploaded file was only partially uploaded.'));
                break;
            case 4:
                add_error(_('No file was uploaded :  Please press the browse button and select a file to upload before you press the next button'));
                break;
        }
    }
    //check for extention
    else if(!in_array($ext,$extentions)){
        add_error("<b>".strtoupper($ext)."</b> : "._("Please upload a gpx file with the extention \".gpx\""));
    }
    //move the uploaded file to the tmp directory
    else if (move_uploaded_file($_FILES['load']['tmp_name'],$_SESSION['gps']['file']))
    {
	
	if(!_shn_gps_file_checker())
	  {	
		
	   shn_gps_point_sort_start();	
	   return;
	  }		
	
    }    else{
        add_error(_('Possible file upload attack!'));
    }
}


//Print the error message If an error occord with the Upload File
display_errors($return=false,$clean_errors=true,$exit=false);
//draw upload form
  _shn_gps_upload_form();
//end of function



function _shn_gps_upload_form()
{
	print '<center><h2>' . _("GPX file upload") . '</h2></center>';

	global $global;
	global $conf;
	include_once $global['approot']."/inc/lib_form.inc";

	
	shn_form_fopen("upload",null,array('enctype'=>'enctype="multipart/form-data"','req_message'=>false));
	shn_form_fsopen(_("Upload GPS data"));
	echo "<p><em><strong>"._('important: ')."</strong></em>"._('This system will only accept gpx files which are welformed and valid.')."</p>";
        shn_form_upload(_('Upload File'),"load"); 
	shn_form_fsclose();

	print "<br />";
	shn_form_submit(_("Upload"));
	shn_form_fclose();

}
function _shn_gps_file_checker()
{
$error_flag=false;

	
class SchemaDOMDocument extends DOMDocument
{
    public function validateXMLSchemas()
    {
        $schemaLocation =$conf['schema_location']; //$this->documentElement->getAttributeNS('http://www.w3.org/2001/XMLSchema-instance', 'schemaLocation');


         $pairs = preg_split('/\s+/', $schemaLocation);
         $pairCount = count($pairs);
         $valid = true;
         for($x = 1; $x < $pairCount; $x+=2) {
             $valid = $this->schemaValidate($pairs[$x]) && $valid;
         }
        
         if(!$valid) {
		return false;
         }

         return true;
    }
}//end of class SchemaDOMDocument


	$file=$_SESSION['gps']['file'];

   if (!($fp = fopen($file, "r"))) {
    add_error(_("Can not open file."));
	unlink($file);
    return $error_flag=true;;
    }
	 
	$xml = fread($fp,filesize($file));
     // close the file
       fclose($fp);

	     $parser = xml_parser_create ();
	if (!xml_parse ($parser, $xml, true)) {
	     xml_parser_free ($parser);
		unlink($file);
	    add_error(_("Your File is not welformed. Please upload a welformed file"));
	 return $error_flag=true;;
	}
	$library = new SchemaDOMDocument("1.0");
	$library->validateOnParse = true;
	$library->load($file);

	if($library->validateXMLSchemas()) {
    add_confirmation(_('The file was uploaded successfully...'));
	 return $error_flag=false;;

	}else{
	unlink($file);
	add_error(_("Your File is not valid. Please upload a valid file"));
	 return $error_flag=true;
	}

}



?>