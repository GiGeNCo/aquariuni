<?php
define('FILE', '/aquariuni/config.cfg');
if (key_exists('submit', $_POST))
{
    $data = 'LOGLEVEL 3\n';
    $data.='LOGTOFILE 0\n';
    unset($_POST['submit']);
    foreach ($_POST as $k => $v)
    {
        $data.=$k.' '.$v.'\n';
    }
    file_put_contents(FILE, $data);
}
?>
<form method="POST">
    <div class="form-group">
        <label class="control-label">LIGHT_HOUR</label>
        <input type="text"  value=""  name="LIGHT_HOUR" class="form-control">
    </div>
    <div class="form-group">
        <label class="control-label">CELSIUS_MIN</label>
        <input type="text"  value=""  name="CELSIUS_MIN" class="form-control">
    </div>
    <div class="form-group">
        <label class="control-label">CELSIUS_MAX</label>
        <input type="text"  value=""  name="CELSIUS_MAX" class="form-control">
    </div>
    <div class="form-group">
        <label class="control-label">HUMIDITY_MIN</label>
        <input type="text"  value=""  name="LIGHT_HOUR" class="form-control">
    </div>
    <div class="margiv-top-10">
        <button type="submit" name="submit" class="btn green">შენახვა</button>
    </div>
</form>