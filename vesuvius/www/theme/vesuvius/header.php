<?php
/**
 * Lost Person Finder v3 Theme HTML Header
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author Greg Miernicki <g@miernicki.com>
 */

global $global;
global $conf;

// Get the Long Name of the incident
function getLongName() {
	global $global;
	global $conf;

	$short = mysql_real_escape_string($_GET['shortname']);

	$long = "";
	$sql = "SELECT name FROM incident WHERE `shortname` = '".$short."' LIMIT 1;";
	$arr = $global['db']->GetAll($sql);
	if (!empty($arr)) {
		foreach($arr as $row) {
			$long = $row['name'];
		}
	}
	return $long;
}

?>
<div id="header" class="clearfix">
	<a href="index.php"><img src="theme/lpf3/img/pl.png"></a>
	<h1><a href="index.php"><?php
		echo _t(getLongName()." People Locator");?>
	</a></h1>
	<h2>U.S. National Library of Medicine<br>
	Lister Hill National Center for Biomedical Communications</h2>
	<?php
	if(isset($conf['enable_locale']) && $conf['enable_locale'] == true) {
		_shn_lc_lang_list();
	}
	?>
</div>
<?