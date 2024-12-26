#include<iostream>
#include<catch.hpp>
#include<vector>
#include<string>
#include<list>
#include<algorithm>
#include<execution>

using namespace std;

bool DoesContentAnyWords(string::iterator str_iter,size_t str_size,size_t words_total_size,list<string>& words) {
	if (words.empty())
		return true;

	if (words_total_size > str_size) {
		return false;
	}

	auto res = find_if(words.begin(), words.end(), [str_iter,str_size](const string &s) {
		if (s.size() > str_size) 
			return false;
		if (*str_iter != s.front())
			return false;
		return equal(s.begin(), s.end(), str_iter);
		});

	if (str_size == 0)
		return false;

	if (res == words.end())
		return false;
	else {

		str_size -= (*res).size();
		str_iter += (*res).size();
		words.erase(res);
		
		return DoesContentAnyWords(str_iter, str_size, 0, words);

	}

	return false;
}


vector<int> findSubstring(string s, vector<string> words) {
	list<string> words_list;
	size_t total_size = 0;
	auto biwl = back_inserter(words_list);
	for_each(words.begin(), words.end(), [&biwl,&total_size](string s) {
		total_size += s.size();
		biwl = s;
		biwl++;
		});
	list<string> temp(words_list);
	vector<int> result{};
	auto str_iter = s.begin();
	for (size_t i = 0; i < s.size(); i++)
	{
		if (DoesContentAnyWords(str_iter,s.size()-i,total_size,temp))
		{
			result.push_back(i);
		}
		if (temp.size()!=words_list.size())
		{
			temp = list<string>(words_list);
		}

		str_iter++;
	}

	return result;
}

TEST_CASE("BASE TEST") {
	REQUIRE(findSubstring("barfoothefoobarman"s, vector<string>{"foo", "bar"}) == vector<int>{0, 9});
	REQUIRE(findSubstring("wordgoodgoodgoodbestword"s, vector<string>{"word", "good", "best", "word"}) == vector<int>{});
	REQUIRE(findSubstring("barfoofoobarthefoobarman"s, vector<string>{"bar", "foo", "the"}) == vector<int>{6, 9, 12});
}

TEST_CASE("SPEED TEST") {
	BENCHMARK("1") {
		return findSubstring("aratdgpfsookqyxiptwjllwirwmfdmafdayignqadektejbvcaepnbyezmlcalkfnkovaeydkixqsalwaqmptmwsajwaxifktvitbgwlqvdiwphyhtochmwhvujsdofymptnvpzlnewjtfhcaxghjeqhzzzepgebvxpqoqebuckqhuuhtbqdfgmghlmwuqypppiefofbqsrzooihpymwgyfnmrlgkjxzaffftnjlfamvoucfurecpjpdcblomjqnovukidvpgikwepebgidxttdxwomkzczqxuaizxxhfkembinjsqglllijcwubytryptgrrfyypekqmxzeqirbvclxyhbxcuxuodlfilfaqqsepulfecjzgwzfdaehubbkeorocxqunjycflkjqtkwpjbsjfbggdqmtibvhtpucqyjbisrbfosopmaxogdryqmitkpmzlrrkatuvmyaaqosdqpryukxkwhfgzuiklzwnurkhpkjfbbirsbqnlpzkyfsxbcimeebyxmhmyruzsctlglytaxfyeyyfcgtgmxfkjowjfqjyveldplwricppcnwevsnkpuuaisjoluoiyzlnkjeulwlpliujahtrdntlhczsxncxonlyxrvkngabowkqffjiuctbhvweiybxmoxlisvvzxyptkiyprijwcndxjjhhmgvbeijwegvdhnxrvxjoiskmfnloysylzvmfexbifznmmmgjkpxujkgpzrfyjfjkbxpfwtpbscqgpwrbnovwadlautyfahqbehiccxdwctcrrvuekrbkuokojktkrlnxvwzxtfuvayosuiygzzstqfjzpfljszinvilqphopfejzpihqjamzfvbuamftloiiyvbncrekvolkytbhtnjakkulwagkqquomvbomhykvkuvdxdykoyvyuiwwqgmgdasydjnlhxitreyrjwbxwyxritnacahfcbdgksrupzpjfoaomdnjekamepngpwlsxqakjrgasvjyjlowpcftohhuwwaounisgiepbkpthbtrmipbmuwcdgxzczpxnxrthxkijbeqcxhphysvuryxzxzbwoalmtgvsqedsiuwhdlrcgmwzmuyjvbijetxzatsszvmjrjqvwhzeuvdirbumdcyhxvizqaspygyprrmoyluuhyfabzpgbnpykyadasuyavosmaimocjxcoxgnooqdeqqeqtekpflktfyvnllruiwigexwsnaydqcwljgaotljyjgnwshsafaijzfdmfcsvgogruifovqohxcdrjwroyazyfcmmgejpsrgnzodvercdtfuedoueotcvyqhgvsvnjeciuhfazheupabuovycrczptixoatdlziutpbtqjzlaamuojvtaxsrsdpidkmplulejmzcxznzbbupkrinqdgjgvrlhdcsznylcynbzcbadxppoaeedlplihwqmzkoojbqjouksvkvubmidtoiegtonqgbrrrfcsynisxanjxhkmrqfhylnszckigbbxgdqeqawpblyyukmlarvzcitelfmtgnqosivkjtzmfxmzjznkqilvsgzflnytcpjwzegkyfwfejgnivzadkvyswdflcyptilsmrdmybrckasuvrxzeszyrceeecuxmfsbxxnvyhalhuhcnedrzcsqfwulyqlnwdovcbsaksnrmvwczztyelqljnwkdhxzmlwooprzheqwzoyzotzuhsfqfbailzkzkgobxfaflsdlhdmxylrhdwykzavkchkmpannhpuskxdrcrocfhkkdkvemqrozddodsbmivesuklybbbgintnxorjgiafldvqxxcfujzptmnwnqfxdymcoemwoobcrwuovxwqgxfbmuzznezselvsrhoivrmoqgeldcdlakomfonuuomzahttqkdndpdvwihzkknmxbaeroymcmneuiamudaytftpncqapdmmhnqadomhcbmwkmlgrneksazicqitvwfelxfontyqvkohyznrmuchubpytxsrvzvhxaxmuvcrhryhsnzfhbmdedcacwrxxmeupejjzlcjeaqxprexssazvezxaquyebuthdegrgrviisybwxuozvleuiemfeqizmpeqxvzprjzljakguagrmmlwszdxqlyeacuyavnrfmeomqxjrfcfrqbjpfihsgltlitldiekwibkzavsfyxyoajdhsnaayvliqyoycyunbgobcggcfgqhqvpkirkjmytcwhcbiyojeelimtkracysypcigotuopynwaoeyeqfibnuwynwcnqcdsnljggxxemuhaafgskovaksyzqcnhfsbsdkalkyswuzzugfnrwiricritvvaandssoveatwynxxjdfywbjpllitgeoiedmzwcwccpyaexapafqzizotmxntddbjhnifrghtxhwdewtgblfjkwcyvrravvjeiujaasvyzrbfnwlqhtbrrgqoxjouexyprjrsdmscgtjvqxoxsprjvjzvunpzkqqebhyfvqjdjtzbspbkeuvcduxxhoytgoxkvvptnawxvxanmbzrvuvaouavkyprpobkmsfzucyqzzfoafhyzcaoyalizczorcafuiepkdhlcmberietmfhkhutgxuwqxzvthbktergieipxqvqfazpiuiqrdphcqevzfgsmzaudildbhtgjvvtpgmglbpptvksasmosmlxvwawfweprbkghwouzfjsawmcqyrilcggaieggkxzlhhvgvrfcbaczmhpnayyeggeqmkzwjyjrgezdwegzgkytrpgtpgxxmcoaopwynhrtmqzkwfjdrjylageqocncgdcusaughnbtfcfchqhbbhmcpssduhfaljxdjtlqhpmmrrqbkzcliqnxihcfpjhcsehdatwhkivbboennizwyovjwyonhvpccyfctbldlghpulckwdgusbfobtdlruntsuvmyiplowalkfvgibcaeiqgdvrupgnickwasnmjkouwvpegsgiwqbeuwxoofeyiquijhwutnorkfvqxezvuaaoyzfmfjknzgxkowgjlubvzwoycnuxpwnnvsccdorfvprlnyuyuvvuujswyovpkjdidhkjveoqvfbifyiatfuproopflfpukzarmjmqxfleivkgdkckgrbwhtbtytpkspdeyruxwhefcqlhcnsihvgookjodzyxodcpvyorisykimukboukjdbankosjppastpnufhcyhoivivxwphisiihvwzenregkvvebcgbmxlhfggewomqywatsbagsgodcjjfosiaptjwcqaagoseksafuanoibrmmdtavbcmxmizcjzizrokmqrgseubhontrhwokyahmiiqthyvbpfnfwvycrzjhmeyvaogboppzyguhgpkvwxbuuzwmahtomukoksrbhhafnwptozpkzshttdhtndhzztpjlhkvomadlrwzrnlsfsnayxtladmbybkmixhyjjbwbavunjmvbzvbwrmywyzwcmikjplszmrammwcvizzjwagpngnngkpsscbinvjbmjqbfsyptxyraghpnueveupxyshlpqoebehiyfxtfxlfeswtoaqtwhsuzzhqrwuscbabjxuqwfxaztvotnjqubmtcuktsgnuknxvmulkbilbbirwwaoqdbmhxycrgpnqellshycigpjjycgwcumhxaowysnfhbxnolhvjkdqbpzbthxycmfbmwynonsyqpleatbmfhcgydkrlhpnvxqktoxjerhugvzjqcvxjzfhcpbnzqcupteijdunudkdyjmqnjnxkvgmkhcjaegpzmalquakxknyvbojmeiwzollynvytdpvrpghlgulthjolzxxdfwewhquwnupslmjbsroblzuuikhkkfnrbunkmjgzfxrrkcuctifgibdqmkcwrsnumdeyokzukqlushyopgwxhzqtmsrdkhyykewyrvubnhxiovwebudjwveioynafnzrsxrltmmitjqkgooiltthpzrdzefeuexocpzxbnhwyageowozqjihjzmigrpaymqcdpzgcidailgxkvyaejjpivaqmpskdimhznnbwsdegmdqheqnnzfxwfqiwivbthksxawvsbbynhowlgmahrzdypouajvtsilpihkajobwvrviyhihyjnwbbsbmpuexhufpgiaujyratzachkctzauasvmkrsjaoprxzrrislklknqszsnythaneoxxghxvypsxilhawtohiebhyqhrxhhdvgaepzbnqvmzgtbfppoxvrfuhongwujtblxqmygdtsecofjdxxasqhoxwcfuyqnbbnuplashuyjiesnbrqvhzkgxmlrmbhoeuithiooeoznstcvmsttsdbrrojdrsrvmbrtlhkqvlfqfhnrcgnulqlcfwiwobucdnyowketvjlctzuvhjrtzexedfdrhzwkmuakghdbsrelsaibjzukeuphzuaityuhuvtaeyewpiihkqjtsfdybufbqhlliiucdndjmhfdrpnbgwwadzyfwfimovawduziierwlxzemmfukbuocsvyzfnoankejjmrnepadpepdjkomgepbzpageogtzkdizwydmyiddxgojubqystzhtfmiofhykrzhpevomytkehvbknbcgdmakyiyfrzsiybadwqpwjzcsxdfkhhrkvtuvbtdssvcqwcvuslqdmsyjydufmnrigldjggdadftzkotezlimeixeltjxgahonlxwtcwxkpyuguaffktlsrpdmydtakjqxjmtliqxaqrgkunqejbxctcorhjustkrewkpgcngtgodcevhpzgrskhlsrfmmrdqpqhwswelfvrhzoqonyhhjotbhaptusljivfbrmoyhhigwywlxdtirojzoyuisiuddbgwnuxwefccdapcdkkxyvyptszoctrfvxektbhzilblororbyqcworpjqflmwtjvztpacqkqsvellvommqiajzlafxodqxbpqsrviblaypnkmeyyugbehmgolwsbtvslnjgvkrylinvvrvvmbwsilazwwraroscbejyqcwblkygdtbrualfnleljxlclgfokqmaslefxclawpssrdzerdrccffplkdxaszuddaainaeeswvywbpbvtgayvnkbkmtlhwrjyzyyddtbatzcidxbjzcgmmjyzejicarabpbeuuivphxxkwavvcejrnhqusawvrxwiyddulyjuxifvkcspgbgwkyqeamzrlyblbghogsifapansscavkwfkokkdldojgcmnjavclbeabrswvvrhtzrildlwgbindwcpzxrkyvkcpfykarutslbdpocxskkxgomfmfrmbcoshmehgyaymecbueamqlmybygnexahzobidfplgsjsynvstvhlitkktszzpzirqjbvptgxlrplhkfahmoqhaadszcjblctweonxwkkpzxwlcztrnjynldhmiqnvvgrzwfyurkkthgejhzawkbjxeskolxjggbheihzzrjsarzjbymxlpjivbskostuaudeckfedowdivplwbihqtpnxixlcricllgqymubcsfmowxkzirrbieaqcmstuwgffwdrshvlokbkjnjtgaxogxhijbbfyildgqwbzrondpznckiimfytdfbmhfsfpfkvxgyxzmmddosfyaplgqelvhzemtjbatzybxxbmlgpzyxyaoliertcytgnosoplppppmqbzwszwpzygmhkdcmdxtqmlhbywqpnefqddjebadagpjtulhyjaovnxyowodjulaxolcsnhsuzbptowtxziuohscdiinctpcjagbnnvjoyaknxdkynfmvzryiznmscodewfumafazgmodsydhfpcfgdpfsdzxudbqkvcmbdnjrbmjarrhgvonafut"s,
			vector<string>{
			"vkyprpobkmsfzucyqzzfoafhyzca", "gdvrupgnickwasnmjkouwvpegsgi", "jzukeuphzuaityuhuvtaeyewpiih", "syzqcnhfsbsdkalkyswuzzugfnrw", "kygdtbrualfnleljxlclgfokqmas", "pqoqebuckqhuuhtbqdfgmghlmwuq", "ycrgpnqellshycigpjjycgwcumhx", "vgogruifovqohxcdrjwroyazyfcm", "lefxclawpssrdzerdrccffplkdxa", "vyqhgvsvnjeciuhfazheupabuovy", "fexbifznmmmgjkpxujkgpzrfyjfj", "qthyvbpfnfwvycrzjhmeyvaogbop", "rvvmbwsilazwwraroscbejyqcwbl", "jzlafxodqxbpqsrviblaypnkmeyy", "vrhzoqonyhhjotbhaptusljivfbr", "trfvxektbhzilblororbyqcworpj", "sybwxuozvleuiemfeqizmpeqxvzp", "bxgdqeqawpblyyukmlarvzcitelf", "tjxgahonlxwtcwxkpyuguaffktls", "ebhyfvqjdjtzbspbkeuvcduxxhoy", "rplhkfahmoqhaadszcjblctweonx", "obxfaflsdlhdmxylrhdwykzavkch", "hykrzhpevomytkehvbknbcgdmaky", "tuvbtdssvcqwcvuslqdmsyjydufm", "bkmtlhwrjyzyyddtbatzcidxbjzc", "nrigldjggdadftzkotezlimeixel", "tjqkgooiltthpzrdzefeuexocpzx", "astpnufhcyhoivivxwphisiihvwz", "plashuyjiesnbrqvhzkgxmlrmbho", "ieaqcmstuwgffwdrshvlokbkjnjt", "dewtgblfjkwcyvrravvjeiujaasv", "hzeuvdirbumdcyhxvizqaspygypr", "bbupkrinqdgjgvrlhdcsznylcynb", "mwzmuyjvbijetxzatsszvmjrjqvw", "lsxqakjrgasvjyjlowpcftohhuww", "datwhkivbboennizwyovjwyonhvp", "stuaudeckfedowdivplwbihqtpnx", "chkctzauasvmkrsjaoprxzrrislk", "sypcigotuopynwaoeyeqfibnuwyn", "izwydmyiddxgojubqystzhtfmiof", "rsrvmbrtlhkqvlfqfhnrcgnulqlc", "tmfhkhutgxuwqxzvthbktergieip", "kmpannhpuskxdrcrocfhkkdkvemq", "pvyorisykimukboukjdbankosjpp", "fahqbehiccxdwctcrrvuekrbkuok", "nuuomzahttqkdndpdvwihzkknmxb", "agpngnngkpsscbinvjbmjqbfsypt", "zcbadxppoaeedlplihwqmzkoojbq", "bgwnuxwefccdapcdkkxyvyptszoc", "xzeszyrceeecuxmfsbxxnvyhalhu", "evhpzgrskhlsrfmmrdqpqhwswelf", "euithiooeoznstcvmsttsdbrrojd", "ibdqmkcwrsnumdeyokzukqlushyo", "babjxuqwfxaztvotnjqubmtcukts", "kqjtsfdybufbqhlliiucdndjmhfd", "csynisxanjxhkmrqfhylnszckigb", "dtsecofjdxxasqhoxwcfuyqnbbnu", "owkqffjiuctbhvweiybxmoxlisvv", "kbxpfwtpbscqgpwrbnovwadlauty", "nepadpepdjkomgepbzpageogtzkd", "mmhnqadomhcbmwkmlgrneksazicq", "rjgiafldvqxxcfujzptmnwnqfxdy", "tgoxkvvptnawxvxanmbzrvuvaoua", "oyalizczorcafuiepkdhlcmberie", "wcnqcdsnljggxxemuhaafgskovak", "tfcfchqhbbhmcpssduhfaljxdjtl", "gdryqmitkpmzlrrkatuvmyaaqosd", "zmhpnayyeggeqmkzwjyjrgezdweg", "qflmwtjvztpacqkqsvellvommqia", "rbhhafnwptozpkzshttdhtndhzzt", "kqmxzeqirbvclxyhbxcuxuodlfil", "epnbyezmlcalkfnkovaeydkixqsa", "crczptixoatdlziutpbtqjzlaamu", "avclbeabrswvvrhtzrildlwgbind", "jbxctcorhjustkrewkpgcngtgodc", "xwhefcqlhcnsihvgookjodzyxodc", "vgmkhcjaegpzmalquakxknyvbojm", "pjlhkvomadlrwzrnlsfsnayxtlad", "rzheqwzoyzotzuhsfqfbailzkzkg", "pbnzqcupteijdunudkdyjmqnjnxk", "zxxdfwewhquwnupslmjbsroblzuu", "zselvsrhoivrmoqgeldcdlakomfo", "qjamzfvbuamftloiiyvbncrekvol", "xyowodjulaxolcsnhsuzbptowtxz", "puuaisjoluoiyzlnkjeulwlpliuj", "dpzgcidailgxkvyaejjpivaqmpsk", "mfbmwynonsyqpleatbmfhcgydkrl", "qhpmmrrqbkzcliqnxihcfpjhcseh", "pflktfyvnllruiwigexwsnaydqcw", "mdedcacwrxxmeupejjzlcjeaqxpr", "bnhwyageowozqjihjzmigrpaymqc", "njsqglllijcwubytryptgrrfyype", "moyhhigwywlxdtirojzoyuisiudd", "gaxogxhijbbfyildgqwbzrondpzn", "qpryukxkwhfgzuiklzwnurkhpkjf", "rjzljakguagrmmlwszdxqlyeacuy", "eivkgdkckgrbwhtbtytpkspdeyru", "ikhkkfnrbunkmjgzfxrrkcuctifg", "sdmscgtjvqxoxsprjvjzvunpzkqq", "mywyzwcmikjplszmrammwcvizzjw", "ixlcricllgqymubcsfmowxkzirrb", "ahtrdntlhczsxncxonlyxrvkngab", "lruntsuvmyiplowalkfvgibcaeiq", "wqpnefqddjebadagpjtulhyjaovn", "eiwzollynvytdpvrpghlgulthjol", "tqfjzpfljszinvilqphopfejzpih", "gnuknxvmulkbilbbirwwaoqdbmhx", "ypouajvtsilpihkajobwvrviyhih", "smlxvwawfweprbkghwouzfjsawmc", "uvvuujswyovpkjdidhkjveoqvfbi", "vyswdflcyptilsmrdmybrckasuvr", "avnrfmeomqxjrfcfrqbjpfihsglt", "rpdmydtakjqxjmtliqxaqrgkunqe", "pmqbzwszwpzygmhkdcmdxtqmlhby", "vvcejrnhqusawvrxwiyddulyjuxi", "aounisgiepbkpthbtrmipbmuwcdg", "nlhxitreyrjwbxwyxritnacahfcb", "wivbthksxawvsbbynhowlgmahrzd", "zxyptkiyprijwcndxjjhhmgvbeij", "zgkytrpgtpgxxmcoaopwynhrtmqz", "zgtbfppoxvrfuhongwujtblxqmyg", "kvkuvdxdykoyvyuiwwqgmgdasydj", "jouksvkvubmidtoiegtonqgbrrrf", "yjnwbbsbmpuexhufpgiaujyratza", "zflnytcpjwzegkyfwfejgnivzadk", "eksafuanoibrmmdtavbcmxmizcjz", "qyrilcggaieggkxzlhhvgvrfcbac", "ayvliqyoycyunbgobcggcfgqhqvp", "wqbeuwxoofeyiquijhwutnorkfvq", "lgkjxzaffftnjlfamvoucfurecpj", "yxzxzbwoalmtgvsqedsiuwhdlrcg", "pdcblomjqnovukidvpgikwepebgi", "lwaqmptmwsajwaxifktvitbgwlqv", "zlnewjtfhcaxghjeqhzzzepgebvx", "jowjfqjyveldplwricppcnwevsnk", "hcnedrzcsqfwulyqlnwdovcbsaks", "kwfjdrjylageqocncgdcusaughnb", "mlgpzyxyaoliertcytgnosoplppp", "nvstvhlitkktszzpzirqjbvptgxl", "ccyfctbldlghpulckwdgusbfobtd", "faqqsepulfecjzgwzfdaehubbkeo", "dgksrupzpjfoaomdnjekamepngpw", "dosfyaplgqelvhzemtjbatzybxxb", "bbirsbqnlpzkyfsxbcimeebyxmhm", "kirkjmytcwhcbiyojeelimtkracy", "yruzsctlglytaxfyeyyfcgtgmxfk", "fxtfxlfeswtoaqtwhsuzzhqrwusc", "xzczpxnxrthxkijbeqcxhphysvur", "itvwfelxfontyqvkohyznrmuchub", "fwiwobucdnyowketvjlctzuvhjrt", "awtohiebhyqhrxhhdvgaepzbnqvm", "mbybkmixhyjjbwbavunjmvbzvbwr", "ywbjpllitgeoiedmzwcwccpyaexa", "pgwxhzqtmsrdkhyykewyrvubnhxi", "iricritvvaandssoveatwynxxjdf", "zexedfdrhzwkmuakghdbsrelsaib", "ypppiefofbqsrzooihpymwgyfnmr", "lknqszsnythaneoxxghxvypsxilh", "rocxqunjycflkjqtkwpjbsjfbggd", "qmtibvhtpucqyjbisrbfosopmaxo", "nrmvwczztyelqljnwkdhxzmlwoop", "vosmaimocjxcoxgnooqdeqqeqtek", "exssazvezxaquyebuthdegrgrvii", "yzrbfnwlqhtbrrgqoxjouexyprjr", "hpnvxqktoxjerhugvzjqcvxjzfhc", "ifapansscavkwfkokkdldojgcmnj", "gmmjyzejicarabpbeuuivphxxkwa", "mtgnqosivkjtzmfxmzjznkqilvsg", "aeroymcmneuiamudaytftpncqapd", "ovwebudjwveioynafnzrsxrltmmi", "litldiekwibkzavsfyxyoajdhsna", "wkkpzxwlcztrnjynldhmiqnvvgrz", "szuddaainaeeswvywbpbvtgayvnk", "kkxgomfmfrmbcoshmehgyaymecbu", "dimhznnbwsdegmdqheqnnzfxwfqi", "xqvqfazpiuiqrdphcqevzfgsmzau", "eamqlmybygnexahzobidfplgsjsy", "pytxsrvzvhxaxmuvcrhryhsnzfhb", "wegvdhnxrvxjoiskmfnloysylzvm", "xezvuaaoyzfmfjknzgxkowgjlubv", "pafqzizotmxntddbjhnifrghtxhw", "lxzemmfukbuocsvyzfnoankejjmr", "rpnbgwwadzyfwfimovawduziierw", "rozddodsbmivesuklybbbgintnxo", "izrokmqrgseubhontrhwokyahmii", "ojvtaxsrsdpidkmplulejmzcxznz", "diwphyhtochmwhvujsdofymptnvp", "dildbhtgjvvtpgmglbpptvksasmo", "rmoyluuhyfabzpgbnpykyadasuya", "ojktkrlnxvwzxtfuvayosuiygzzs", "ugbehmgolwsbtvslnjgvkrylinvv", "mcoemwoobcrwuovxwqgxfbmuzzne", "aowysnfhbxnolhvjkdqbpzbthxyc", "mgejpsrgnzodvercdtfuedoueotc", "fyiatfuproopflfpukzarmjmqxfl", "zwoycnuxpwnnvsccdorfvprlnyuy", "ckiimfytdfbmhfsfpfkvxgyxzmmd", "kytbhtnjakkulwagkqquomvbomhy", "dxttdxwomkzczqxuaizxxhfkembi", "fvkcspgbgwkyqeamzrlyblbghogs", "wcpzxrkyvkcpfykarutslbdpocxs", "enregkvvebcgbmxlhfggewomqywa", "iyfrzsiybadwqpwjzcsxdfkhhrkv", "wfyurkkthgejhzawkbjxeskolxjg", "xyraghpnueveupxyshlpqoebehiy", "gbheihzzrjsarzjbymxlpjivbsko", "pzyguhgpkvwxbuuzwmahtomukoks", "tsbagsgodcjjfosiaptjwcqaagos", "ljgaotljyjgnwshsafaijzfdmfcs"
		});
	};

	BENCHMARK("2") {
		return findSubstring("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"s,
			vector<string>(5000,"a"));
	};
}

int main(int argc, char* argv[]) {
	int result = Catch::Session().run(argc, argv);
	return result;
}