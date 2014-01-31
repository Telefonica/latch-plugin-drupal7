<?php 
/*
Latch Drupal 7 plugin - Integrates Latch into the Drupal 7 authentication process.
Copyright (C) 2013 Eleven Paths

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
 * Generates the structure for the second factor form.
 */
function latchTwoFactorForm() {
    $form = array(
        '#id' => 'user_login_block'
    );
    $form['twoFactor'] = array(
        '#type' => 'textfield',
        '#title' => t('Type your one-time password'),
        '#size' => 20
    );
    $form['name'] = array(
        '#type' => 'hidden',
        '#value' => $_POST['name'] // It's automatically encoded by the form builder
    );
    $form['pass'] = array(
        '#type' => 'hidden',
        '#value' => $_POST['pass'] // It's automatically encoded by the form builder
    );
    $form['#validate'] = user_login_default_validators();
    $form['submit'] = array('#type' => 'submit', '#value' => t('Log in'), '#weight' => 2);

    return $form;
}

/*
 * Inserts the rendered second factor form into an HTML document.
 */
function buildHTML($htmlStructure) {
    global $base_url;
    return '<html><head>'
            . '<style>'
            . '.twoFactorContainer { display:block; width:300px; margin: 5% auto 0 auto; text-align: center; border: solid 1px rgb(184, 184, 184); border-radius:5px}'
            . '.twoFactorHeader {float:left; background: #00b9be; color: #FFF; width:100%; border-top-left-radius: 5px; border-top-right-radius: 5px; font-family: sans-serif;}'
            . '.twoFactorHeader h3 {float: left; margin-left: 10px;}'
            . '.twoFactorHeader img {width: 45px; height: auto; float:left; margin-top: 5px; margin-left:20px}'
            . '.twoFactorForm {clear:left; padding-top:10px;}'
            . 'input {margin-top:10px}'
            . 'input[type="submit"] {width:65px;}'
            . '</style>'
            . '</head><body>'
            . '<div class="twoFactorContainer">'
            . '<div class="twoFactorHeader"><img src="' . $base_url . '/sites/all/modules/latch/symbol.png"><h3>One-time password</h3></div><div class="twoFactorForm">'
            . drupal_render($htmlStructure)
            . '</div></body></html>';
}

/*
 * Points the second factor form to the login action
 */
function latch_form_alter(&$form, $form_state, $form_id) {
    if ($form_id == "latchTwoFactorForm") {
        $form['form_id']['#value'] = 'user_login_block';
    }
}

function storeSecondFactor($otp, $uid) {
    db_update('latch')->fields(array('two_factor' => $otp))->condition('uid', $uid)->execute();
}

function retrieveSecondFactor($uid) {
    $query = db_query("SELECT * FROM {latch} WHERE uid=:uid", array(':uid' => $uid));
    $userLatchData = $query->fetchObject();
    return ($userLatchData) ? $userLatchData->two_factor : NULL;
}

function removeSecondFactor($uid) {
    db_update('latch')->fields(array('two_factor' => NULL))->condition('uid', $uid)->execute();
}
